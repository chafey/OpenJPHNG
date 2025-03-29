#include "reversible_forward_vertical_step.h"
#include <arm_neon.h>
#include <cstdio>
#include <openjph/wavelet/reversible_lifting_step.h>

using namespace openjph;
using namespace wavelet;
namespace openjph
{
namespace wavelet
{
namespace neon
{
namespace reversible
{

// The general definition of the wavelet in Part 2 is slightly
// different to part 2, although they are mathematically equivalent
// here, we identify the simpler form from Part 1 and employ them

/////////////////////////////////////////////////////////////////////////
void neon_forward_vertical_step(const ReversibleLiftingStep &lifting_step,
                                const std::span<const si32> &upper_line,
                                const std::span<const si32> &lower_line,
                                const std::span<si32> &destination)
{

    int32_t *dst = destination.data();
    int32_t *destEnd = dst + destination.size();
    const int32_t *src1 = upper_line.data();
    const int32_t *src2 = lower_line.data();
    // general case
    auto va = vdupq_n_s32(lifting_step.lifting_coefficient());
    auto vb = vdupq_n_s32(lifting_step.beta());
    // NOTE: NEON doesn't have a shift right so we use shift left with a negative value, hence ve = -e
    auto ve = vdupq_n_s32(-lifting_step.epsilon());
    size_t i = destination.size();
    for (; i > 0; i -= 4, dst += 4, src1 += 4, src2 += 4)
    {
        auto s1 = vld1q_s32(src1);
        auto s2 = vld1q_s32(src2);
        auto d = vld1q_s32(dst);
        auto t = vaddq_s32(s1, s2);
        auto u = vmulq_s32(va, t);
        auto v = vaddq_s32(vb, u); // haddq_s32
        auto w = vshlq_s32(v, ve);
        d = vaddq_s32(d, w);
        vst1q_s32(dst, d);
    }
}
} // namespace reversible
} // namespace neon
} // namespace wavelet
} // namespace openjph
