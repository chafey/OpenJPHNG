#include <openjph/line_buf.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/param_atk.h>

using namespace openjph;
using namespace wavelet;
namespace openjph
{
namespace wavelet
{
namespace general
{
namespace reversible
{

/////////////////////////////////////////////////////////////////////////
void gen_rev_vert_step32_original(const lifting_step *s,
                                  const line_buf *sig,
                                  const line_buf *other,
                                  const line_buf *aug,
                                  ui32 repeat,
                                  bool synthesis)
{
    const si32 a = s->rev.Aatk;
    const si32 b = s->rev.Batk;
    const ui8 e = s->rev.Eatk;


    si32 *dst = aug->i32;
    const si32 *src1 = sig->i32, *src2 = other->i32;
    // The general definition of the wavelet in Part 2 is slightly
    // different to part 2, although they are mathematically equivalent
    // here, we identify the simpler form from Part 1 and employ them
    if (a == 1)
    { // 5/3 update and any case with a == 1
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (b + *src1++ + *src2++) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (b + *src1++ + *src2++) >> e;
    }
    else if (a == -1 && b == 1 && e == 1)
    { // 5/3 predict
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (*src1++ + *src2++) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (*src1++ + *src2++) >> e;
    }
    else if (a == -1)
    { // any case with a == -1, which is not 5/3 predict
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (b - (*src1++ + *src2++)) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (b - (*src1++ + *src2++)) >> e;
    }
    else
    { // general case
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (b + a * (*src1++ + *src2++)) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (b + a * (*src1++ + *src2++)) >> e;
    }
}

/////////////////////////////////////////////////////////////////////////
void gen_rev_vert_step64_original(const lifting_step *s,
                                  const line_buf *sig,
                                  const line_buf *other,
                                  const line_buf *aug,
                                  ui32 repeat,
                                  bool synthesis)
{
    const si64 a = s->rev.Aatk;
    const si64 b = s->rev.Batk;
    const ui8 e = s->rev.Eatk;

    si64 *dst = aug->i64;
    const si64 *src1 = sig->i64, *src2 = other->i64;
    // The general definition of the wavelet in Part 2 is slightly
    // different to part 2, although they are mathematically equivalent
    // here, we identify the simpler form from Part 1 and employ them
    if (a == 1)
    { // 5/3 update and any case with a == 1
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (b + *src1++ + *src2++) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (b + *src1++ + *src2++) >> e;
    }
    else if (a == -1 && b == 1 && e == 1)
    { // 5/3 predict
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (*src1++ + *src2++) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (*src1++ + *src2++) >> e;
    }
    else if (a == -1)
    { // any case with a == -1, which is not 5/3 predict
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (b - (*src1++ + *src2++)) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (b - (*src1++ + *src2++)) >> e;
    }
    else
    { // general case
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (b + a * (*src1++ + *src2++)) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (b + a * (*src1++ + *src2++)) >> e;
    }
}
} // namespace reversible
} // namespace general
} // namespace wavelet
} // namespace openjph
