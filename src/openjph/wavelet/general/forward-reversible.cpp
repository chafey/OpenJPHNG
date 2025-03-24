#include <openjph/wavelet/wavelet.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/line_buf.h>
#include <openjph/wavelet/general/forward-reversible.h>

using namespace openjph;
using namespace wavelet;
using namespace reversible;

general::ForwardTransform::~ForwardTransform() {

}




/////////////////////////////////////////////////////////////////////////
static
void gen_rev_vert_step32(const lifting_step* s, const line_buf* sig,
                         const line_buf* other, const line_buf* aug,
                         ui32 repeat, bool synthesis)
{
  const si32 a = s->rev.Aatk;
  const si32 b = s->rev.Batk;
  const ui8 e = s->rev.Eatk;

  si32* dst = aug->i32;
  const si32* src1 = sig->i32, * src2 = other->i32;
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
  else { // general case
    if (synthesis)
      for (ui32 i = repeat; i > 0; --i)
        *dst++ -= (b + a * (*src1++ + *src2++)) >> e;
    else
      for (ui32 i = repeat; i > 0; --i)
        *dst++ += (b + a * (*src1++ + *src2++)) >> e;
  }
}

/////////////////////////////////////////////////////////////////////////
static
void gen_rev_vert_step64(const lifting_step* s, const line_buf* sig,
                         const line_buf* other, const line_buf* aug,
                         ui32 repeat, bool synthesis)
{
  const si64 a = s->rev.Aatk;
  const si64 b = s->rev.Batk;
  const ui8 e = s->rev.Eatk;

  si64* dst = aug->i64;
  const si64* src1 = sig->i64, * src2 = other->i64;
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
  else { // general case
    if (synthesis)
      for (ui32 i = repeat; i > 0; --i)
        *dst++ -= (b + a * (*src1++ + *src2++)) >> e;
    else
      for (ui32 i = repeat; i > 0; --i)
        *dst++ += (b + a * (*src1++ + *src2++)) >> e;
  }
}

void general::ForwardTransform::VerticalStep(
    const lifting_step* s,
    const line_buf* sig,
    const line_buf* other,
    const line_buf* aug,
    ui32 repeat,
    bool synthesis) {
        if (((sig != NULL) && (sig->flags & line_buf::LFT_32BIT)) ||
        ((aug != NULL) && (aug->flags & line_buf::LFT_32BIT)) ||
        ((other != NULL) && (other->flags & line_buf::LFT_32BIT)))
    {
      assert((sig == NULL || sig->flags & line_buf::LFT_32BIT) &&
             (other == NULL || other->flags & line_buf::LFT_32BIT) &&
             (aug == NULL || aug->flags & line_buf::LFT_32BIT));
      gen_rev_vert_step32(s, sig, other, aug, repeat, synthesis);
    }
    else
    {
      assert((sig == NULL || sig->flags & line_buf::LFT_64BIT) &&
             (other == NULL || other->flags & line_buf::LFT_64BIT) &&
             (aug == NULL || aug->flags & line_buf::LFT_64BIT));
      gen_rev_vert_step64(s, sig, other, aug, repeat, synthesis);
    }
}

void general::ForwardTransform::HorizontalAna(
    const param_atk* atk,
    const line_buf* ldst,
    const line_buf* hdst,
    const line_buf* src,
    ui32 width,
    bool even) {

}
