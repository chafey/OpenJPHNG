#include <openjph/wavelet/wavelet.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/param_atk.h>
#include <openjph/line_buf.h>
#include <openjph/wavelet/general/reversible-forward-transform.h>

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

    /////////////////////////////////////////////////////////////////////////
    static
    void gen_rev_horz_ana32(const param_atk* atk, const line_buf* ldst, 
                            const line_buf* hdst, const line_buf* src, 
                            ui32 width, bool even)
    {
      if (width > 1)
      {
        // combine both lsrc and hsrc into dst
        si32* dph = hdst->i32;
        si32* dpl = ldst->i32;
        si32* sp = src->i32;
        ui32 w = width;
        if (!even)
        {
          *dph++ = *sp++; --w;
        }
        for (; w > 1; w -= 2)
        {
          *dpl++ = *sp++; *dph++ = *sp++;
        }
        if (w)
        {
          *dpl++ = *sp++; --w;
        }

        si32* hp = hdst->i32, * lp = ldst->i32;
        ui32 l_width = (width + (even ? 1 : 0)) >> 1;  // low pass
        ui32 h_width = (width + (even ? 0 : 1)) >> 1;  // high pass
        ui32 num_steps = atk->get_num_steps();
        for (ui32 j = num_steps; j > 0; --j)
        {
          // first lifting step
          const lifting_step* s = atk->get_step(j - 1);
          const si32 a = s->rev.Aatk;
          const si32 b = s->rev.Batk;
          const ui8 e = s->rev.Eatk;

          // extension
          lp[-1] = lp[0];
          lp[l_width] = lp[l_width - 1];
          // lifting step
          const si32* sp = lp + (even ? 1 : 0);
          si32* dp = hp;
          if (a == 1) 
          { // 5/3 update and any case with a == 1
            for (ui32 i = h_width; i > 0; --i, sp++, dp++)
              *dp += (b + (sp[-1] + sp[0])) >> e;
          }
          else if (a == -1 && b == 1 && e == 1)
          {  // 5/3 predict
            for (ui32 i = h_width; i > 0; --i, sp++, dp++)
              *dp -= (sp[-1] + sp[0]) >> e;
          }
          else if (a == -1)
          { // any case with a == -1, which is not 5/3 predict
            for (ui32 i = h_width; i > 0; --i, sp++, dp++)
              *dp += (b - (sp[-1] + sp[0])) >> e;
          }
          else {
            // general case
            for (ui32 i = h_width; i > 0; --i, sp++, dp++)
              *dp += (b + a * (sp[-1] + sp[0])) >> e;
          }

          // swap buffers
          si32* t = lp; lp = hp; hp = t;
          even = !even;
          ui32 w = l_width; l_width = h_width; h_width = w;
        }
      }
      else {
        if (even)
          ldst->i32[0] = src->i32[0];
        else
          hdst->i32[0] = src->i32[0] << 1;
      }
    }

    /////////////////////////////////////////////////////////////////////////
    static
    void gen_rev_horz_ana64(const param_atk* atk, const line_buf* ldst, 
                            const line_buf* hdst, const line_buf* src, 
                            ui32 width, bool even)
    {
      if (width > 1)
      {
        // combine both lsrc and hsrc into dst
        si64* dph = hdst->i64;
        si64* dpl = ldst->i64;
        si64* sp = src->i64;
        ui32 w = width;
        if (!even)
        {
          *dph++ = *sp++; --w;
        }
        for (; w > 1; w -= 2)
        {
          *dpl++ = *sp++; *dph++ = *sp++;
        }
        if (w)
        {
          *dpl++ = *sp++; --w;
        }

        si64* hp = hdst->i64, * lp = ldst->i64;
        ui32 l_width = (width + (even ? 1 : 0)) >> 1;  // low pass
        ui32 h_width = (width + (even ? 0 : 1)) >> 1;  // high pass
        ui32 num_steps = atk->get_num_steps();
        for (ui32 j = num_steps; j > 0; --j)
        {
          // first lifting step
          const lifting_step* s = atk->get_step(j - 1);
          const si64 a = s->rev.Aatk;
          const si64 b = s->rev.Batk;
          const ui8 e = s->rev.Eatk;

          // extension
          lp[-1] = lp[0];
          lp[l_width] = lp[l_width - 1];
          // lifting step
          const si64* sp = lp + (even ? 1 : 0);
          si64* dp = hp;
          if (a == 1) 
          { // 5/3 update and any case with a == 1
            for (ui32 i = h_width; i > 0; --i, sp++, dp++)
              *dp += (b + (sp[-1] + sp[0])) >> e;
          }
          else if (a == -1 && b == 1 && e == 1)
          {  // 5/3 predict
            for (ui32 i = h_width; i > 0; --i, sp++, dp++)
              *dp -= (sp[-1] + sp[0]) >> e;
          }
          else if (a == -1)
          { // any case with a == -1, which is not 5/3 predict
            for (ui32 i = h_width; i > 0; --i, sp++, dp++)
              *dp += (b - (sp[-1] + sp[0])) >> e;
          }
          else {
            // general case
            for (ui32 i = h_width; i > 0; --i, sp++, dp++)
              *dp += (b + a * (sp[-1] + sp[0])) >> e;
          }

          // swap buffers
          si64* t = lp; lp = hp; hp = t;
          even = !even;
          ui32 w = l_width; l_width = h_width; h_width = w;
        }
      }
      else {
        if (even)
          ldst->i64[0] = src->i64[0];
        else
          hdst->i64[0] = src->i64[0] << 1;
      }
    }

void general::ForwardTransform::HorizontalAna(
    const param_atk* atk,
    const line_buf* ldst,
    const line_buf* hdst,
    const line_buf* src,
    ui32 width,
    bool even) {
      if (src->flags & line_buf::LFT_32BIT) 
      {
        assert((ldst == NULL || ldst->flags & line_buf::LFT_32BIT) &&
               (hdst == NULL || hdst->flags & line_buf::LFT_32BIT));
        gen_rev_horz_ana32(atk, ldst, hdst, src, width, even);
      }
      else 
      {
        assert((ldst == NULL || ldst->flags & line_buf::LFT_64BIT) &&
               (hdst == NULL || hdst->flags & line_buf::LFT_64BIT) && 
               (src == NULL || src->flags & line_buf::LFT_64BIT));
        gen_rev_horz_ana64(atk, ldst, hdst, src, width, even);
      }

}
