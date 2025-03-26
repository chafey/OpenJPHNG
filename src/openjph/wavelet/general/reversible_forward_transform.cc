#include "reversible_horizontal_ana.h"
#include "reversible_vertical_step.h"
#include <openjph/line_buf.h>
#include <openjph/wavelet/general/reversible_forward_transform.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/param_atk.h>

using namespace openjph;
using namespace wavelet;

general::reversible::ForwardTransform::~ForwardTransform()
{
}

void general::reversible::ForwardTransform::VerticalStep(const lifting_step *s,
                                                         const line_buf *sig,
                                                         const line_buf *other,
                                                         const line_buf *aug,
                                                         ui32 repeat,
                                                         bool synthesis)
{
    if (((sig != NULL) && (sig->flags & line_buf::LFT_32BIT)) ||
        ((aug != NULL) && (aug->flags & line_buf::LFT_32BIT)) ||
        ((other != NULL) && (other->flags & line_buf::LFT_32BIT)))
    {
        assert((sig == NULL || sig->flags & line_buf::LFT_32BIT) &&
               (other == NULL || other->flags & line_buf::LFT_32BIT) &&
               (aug == NULL || aug->flags & line_buf::LFT_32BIT));
        reversible::gen_rev_vert_step32(s, sig, other, aug, repeat, synthesis);
    }
    else
    {
        assert((sig == NULL || sig->flags & line_buf::LFT_64BIT) &&
               (other == NULL || other->flags & line_buf::LFT_64BIT) &&
               (aug == NULL || aug->flags & line_buf::LFT_64BIT));
        reversible::gen_rev_vert_step64(s, sig, other, aug, repeat, synthesis);
    }
}

void general::reversible::ForwardTransform::HorizontalAna(const param_atk *atk,
                                                          const line_buf *ldst,
                                                          const line_buf *hdst,
                                                          const line_buf *src,
                                                          ui32 width,
                                                          bool even)
{
    if (src->flags & line_buf::LFT_32BIT)
    {
        assert((ldst == NULL || ldst->flags & line_buf::LFT_32BIT) &&
               (hdst == NULL || hdst->flags & line_buf::LFT_32BIT));
        reversible::gen_rev_horz_ana32(atk, ldst, hdst, src, width, even);
    }
    else
    {
        assert((ldst == NULL || ldst->flags & line_buf::LFT_64BIT) &&
               (hdst == NULL || hdst->flags & line_buf::LFT_64BIT) &&
               (src == NULL || src->flags & line_buf::LFT_64BIT));
        reversible::gen_rev_horz_ana64(atk, ldst, hdst, src, width, even);
    }
}
