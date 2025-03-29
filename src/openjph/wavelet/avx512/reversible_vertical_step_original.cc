 #include <cstdio>
#include <openjph/line_buf.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/param_atk.h>

/*#include "ojph_defs.h"
#include "ojph_arch.h"
#include "ojph_mem.h"
#include "ojph_params.h"
#include "../codestream/ojph_params_local.h"

#include "ojph_transform.h"
#include "ojph_transform_local.h"
*/
#include <immintrin.h>

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

 
 /////////////////////////////////////////////////////////////////////////
    void avx512_rev_vert_step32(const lifting_step* s, const line_buf* sig, 
                                const line_buf* other, const line_buf* aug, 
                                ui32 repeat, bool synthesis)
    {
      const si32 a = s->rev.Aatk;
      const si32 b = s->rev.Batk;
      const ui8 e = s->rev.Eatk;
      __m512i va = _mm512_set1_epi32(a);
      __m512i vb = _mm512_set1_epi32(b);

      si32* dst = aug->i32;
      const si32* src1 = sig->i32, * src2 = other->i32;
      // The general definition of the wavelet in Part 2 is slightly 
      // different to part 2, although they are mathematically equivalent
      // here, we identify the simpler form from Part 1 and employ them
      if (a == 1)
      { // 5/3 update and any case with a == 1
        int i = (int)repeat;
        if (synthesis)
          for (; i > 0; i -= 16, dst += 16, src1 += 16, src2 += 16)
          {
            __m512i s1 = _mm512_load_si512((__m512i*)src1);
            __m512i s2 = _mm512_load_si512((__m512i*)src2);
            __m512i d = _mm512_load_si512((__m512i*)dst);
            __m512i t = _mm512_add_epi32(s1, s2);
            __m512i v = _mm512_add_epi32(vb, t);
            __m512i w = _mm512_srai_epi32(v, e);
            d = _mm512_sub_epi32(d, w);
            _mm512_store_si512((__m512i*)dst, d);
          }
        else
          for (; i > 0; i -= 16, dst += 16, src1 += 16, src2 += 16)
          {
            __m512i s1 = _mm512_load_si512((__m512i*)src1);
            __m512i s2 = _mm512_load_si512((__m512i*)src2);
            __m512i d = _mm512_load_si512((__m512i*)dst);
            __m512i t = _mm512_add_epi32(s1, s2);
            __m512i v = _mm512_add_epi32(vb, t);
            __m512i w = _mm512_srai_epi32(v, e);
            d = _mm512_add_epi32(d, w);
            _mm512_store_si512((__m512i*)dst, d);
          }
      }
      else if (a == -1 && b == 1 && e == 1)
      { // 5/3 predict
        int i = (int)repeat;
        if (synthesis)
          for (; i > 0; i -= 16, dst += 16, src1 += 16, src2 += 16)
          {
            __m512i s1 = _mm512_load_si512((__m512i*)src1);
            __m512i s2 = _mm512_load_si512((__m512i*)src2);
            __m512i d = _mm512_load_si512((__m512i*)dst);
            __m512i t = _mm512_add_epi32(s1, s2);
            __m512i w = _mm512_srai_epi32(t, e);
            d = _mm512_add_epi32(d, w);
            _mm512_store_si512((__m512i*)dst, d);
          }
        else
          for (; i > 0; i -= 16, dst += 16, src1 += 16, src2 += 16)
          {
            __m512i s1 = _mm512_load_si512((__m512i*)src1);
            __m512i s2 = _mm512_load_si512((__m512i*)src2);
            __m512i d = _mm512_load_si512((__m512i*)dst);
            __m512i t = _mm512_add_epi32(s1, s2);
            __m512i w = _mm512_srai_epi32(t, e);
            d = _mm512_sub_epi32(d, w);
            _mm512_store_si512((__m512i*)dst, d);
          }
      }
      else if (a == -1)
      { // any case with a == -1, which is not 5/3 predict
        int i = (int)repeat;
        if (synthesis)
          for (; i > 0; i -= 16, dst += 16, src1 += 16, src2 += 16)
          {
            __m512i s1 = _mm512_load_si512((__m512i*)src1);
            __m512i s2 = _mm512_load_si512((__m512i*)src2);
            __m512i d = _mm512_load_si512((__m512i*)dst);
            __m512i t = _mm512_add_epi32(s1, s2);
            __m512i v = _mm512_sub_epi32(vb, t);
            __m512i w = _mm512_srai_epi32(v, e);
            d = _mm512_sub_epi32(d, w);
            _mm512_store_si512((__m512i*)dst, d);
          }
        else
          for (; i > 0; i -= 16, dst += 16, src1 += 16, src2 += 16)
          {
            __m512i s1 = _mm512_load_si512((__m512i*)src1);
            __m512i s2 = _mm512_load_si512((__m512i*)src2);
            __m512i d = _mm512_load_si512((__m512i*)dst);
            __m512i t = _mm512_add_epi32(s1, s2);
            __m512i v = _mm512_sub_epi32(vb, t);
            __m512i w = _mm512_srai_epi32(v, e);
            d = _mm512_add_epi32(d, w);
            _mm512_store_si512((__m512i*)dst, d);
          }
      }
      else { // general case
        int i = (int)repeat;
        if (synthesis)
          for (; i > 0; i -= 16, dst += 16, src1 += 16, src2 += 16)
          {
            __m512i s1 = _mm512_load_si512((__m512i*)src1);
            __m512i s2 = _mm512_load_si512((__m512i*)src2);
            __m512i d = _mm512_load_si512((__m512i*)dst);
            __m512i t = _mm512_add_epi32(s1, s2);
            __m512i u = _mm512_mullo_epi32(va, t);
            __m512i v = _mm512_add_epi32(vb, u);
            __m512i w = _mm512_srai_epi32(v, e);
            d = _mm512_sub_epi32(d, w);
            _mm512_store_si512((__m512i*)dst, d);
          }
        else
          for (; i > 0; i -= 16, dst += 16, src1 += 16, src2 += 16)
          {
            __m512i s1 = _mm512_load_si512((__m512i*)src1);
            __m512i s2 = _mm512_load_si512((__m512i*)src2);
            __m512i d = _mm512_load_si512((__m512i*)dst);
            __m512i t = _mm512_add_epi32(s1, s2);
            __m512i u = _mm512_mullo_epi32(va, t);
            __m512i v = _mm512_add_epi32(vb, u);
            __m512i w = _mm512_srai_epi32(v, e);
            d = _mm512_add_epi32(d, w);
            _mm512_store_si512((__m512i*)dst, d);
          }
      }
    }
}
}
}
}
