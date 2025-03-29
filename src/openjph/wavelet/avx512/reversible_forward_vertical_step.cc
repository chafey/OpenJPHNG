#include "reversible_forward_vertical_step.h"
#include <cstdio>
#include <immintrin.h>
#include <openjph/wavelet/reversible_lifting_step.h>

using namespace openjph;
using namespace wavelet;
namespace openjph
{
namespace wavelet
{
namespace avx512
{
namespace reversible
{

// The general definition of the wavelet in Part 2 is slightly
// different to part 2, although they are mathematically equivalent
// here, we identify the simpler form from Part 1 and employ them

void avx512_reversible_forward_vertial_step_refactored(const ReversibleLiftingStep &lifting_step,
                                                       const std::span<const si32> &upper_line,
                                                       const std::span<const si32> &lower_line,
                                                       const std::span<si32> &destination)
{
    if (lifting_step.lifting_coefficient() == 1 && lifting_step.beta() == 0 && lifting_step.epsilon() == 1)
    {
        avx512_reversible_forward_vertial_step_c1_b0_e1(upper_line, lower_line, destination);
        return;
    }
    else if (lifting_step.lifting_coefficient() == -1)
    {
        if (lifting_step.beta() == 1 && lifting_step.epsilon() == 1)
        {
            avx512_reversible_forward_vertial_step_cn1_b1_e1(upper_line, lower_line, destination);
            return;
        }
        else
        {
            avx512_reversible_forward_vertial_step_cn1(lifting_step.beta(),
                                                       lifting_step.epsilon(),
                                                       upper_line,
                                                       lower_line,
                                                       destination);
            return;
        }
    }
    // general case
    avx512_reversible_forward_vertial_step_general(lifting_step, upper_line, lower_line, destination);
}

/////////////////////////////////////////////////////////////////////////
void avx512_reversible_forward_vertial_step_general(const ReversibleLiftingStep &lifting_step,
                                                    const std::span<const si32> &upper_line,
                                                    const std::span<const si32> &lower_line,
                                                    const std::span<si32> &destination)
{

    __m512i *dst = (__m512i *)destination.data();
    const __m512i *src1 = (__m512i *)upper_line.data();
    const __m512i *src2 = (__m512i *)lower_line.data();
    __m512i va = _mm512_set1_epi32(lifting_step.lifting_coefficient());
    __m512i vb = _mm512_set1_epi32(lifting_step.beta());
    auto e = lifting_step.epsilon();
    int i = destination.size() >> 4;

    for (; i > 0;)
    {
        __m512i s1 = _mm512_load_si512(src1);
        __m512i s2 = _mm512_load_si512(src2);
        __m512i t = _mm512_add_epi32(s1, s2);
        __m512i d = _mm512_load_si512(dst);
        __m512i u = _mm512_mullo_epi32(va, t);
        __m512i v = _mm512_add_epi32(vb, u);
        __m512i w = _mm512_srai_epi32(v, e);
        d = _mm512_add_epi32(d, w);
        _mm512_store_si512(dst, d);
        ++src1;
        ++src2;
        ++dst;
        --i;
    }
}
void avx512_reversible_forward_vertial_step_c1_b0_e1(const std::span<const si32> &upper_line,
                                                     const std::span<const si32> &lower_line,
                                                     const std::span<si32> &destination)
{
    __m512i *dst = (__m512i *)destination.data();
    const __m512i *src1 = (__m512i *)upper_line.data();
    const __m512i *src2 = (__m512i *)lower_line.data();
    int i = destination.size() >> 4;

    for (; i > 0;)
    {
        __m512i s1 = _mm512_load_si512(src1);
        __m512i s2 = _mm512_load_si512(src2);
        __m512i t = _mm512_add_epi32(s1, s2);
        __m512i d = _mm512_load_si512(dst);
        __m512i w = _mm512_srai_epi32(t, 1);
        d = _mm512_add_epi32(d, w);
        _mm512_store_si512(dst, d);
        ++src1;
        ++src2;
        ++dst;
        --i;
    }
}
void avx512_reversible_forward_vertial_step_cn1_b1_e1(const std::span<const si32> &upper_line,
                                                      const std::span<const si32> &lower_line,
                                                      const std::span<si32> &destination)
{
    __m512i *dst = (__m512i *)destination.data();
    const __m512i *src1 = (__m512i *)upper_line.data();
    const __m512i *src2 = (__m512i *)lower_line.data();
    int i = destination.size() >> 4;

    for (; i > 0;)
    {
        __m512i s1 = _mm512_load_si512(src1);
        __m512i s2 = _mm512_load_si512(src2);
        __m512i t = _mm512_add_epi32(s1, s2);
        __m512i d = _mm512_load_si512(dst);
        __m512i w = _mm512_srai_epi32(t, 1);
        d = _mm512_sub_epi32(d, w);
        _mm512_store_si512(dst, d);
        ++src1;
        ++src2;
        ++dst;
        --i;
    }
}
void avx512_reversible_forward_vertial_step_cn1(si16 beta,
                                                ui8 epsilon,
                                                const std::span<const si32> &upper_line,
                                                const std::span<const si32> &lower_line,
                                                const std::span<si32> &destination)
{
    __m512i *dst = (__m512i *)destination.data();
    const __m512i *src1 = (__m512i *)upper_line.data();
    const __m512i *src2 = (__m512i *)lower_line.data();
    const __m512i vb = _mm512_set1_epi32(beta);
    int i = destination.size() >> 4;

    for (; i > 0;)
    {
        __m512i s1 = _mm512_load_si512(src1);
        __m512i s2 = _mm512_load_si512(src2);
        __m512i t = _mm512_add_epi32(s1, s2);
        __m512i d = _mm512_load_si512(dst);
        __m512i v = _mm512_sub_epi32(vb, t);
        __m512i w = _mm512_srai_epi32(v, epsilon);
        d = _mm512_add_epi32(d, w);
        _mm512_store_si512((__m512i *)dst, d);
        ++src1;
        ++src2;
        ++dst;
        --i;
    }
}
} // namespace reversible
} // namespace avx512
} // namespace wavelet
} // namespace openjph