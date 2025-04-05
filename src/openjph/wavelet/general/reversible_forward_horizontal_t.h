#ifndef OPENJPH_WAVELET_REVERSIBLE_FORWARD_HORIZONTAL_T_H
#define OPENJPH_WAVELET_REVERSIBLE_FORWARD_HORIZONTAL_T_H

#include <cassert>
#include <openjph/common.h>
#include <openjph/line_buf.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/param_atk.h>
#include <openjph/wavelet/reversible_lifting_step.h>
#include <span>
#pragma once

namespace openjph
{

namespace wavelet
{

using namespace openjph;
using namespace std;

union lifting_step;

namespace general
{

namespace reversible
{
// The general definition of the wavelet in Part 2 is slightly
// different to part 2, although they are mathematically equivalent
// here, we identify the simpler form from Part 1 and employ them

/**
 * The general case for wavelet forward vertical step transform
 */
template <typename T>
void reversible_forward_horizontal_general(const ReversibleLiftingStep &s,
                                           const std::span<const T> &source,
                                           const std::span<T> &destination)
{
    assert(source.size() >= destination.size());

    auto source_iterator = std::cbegin(source);
#pragma clang loop vectorize(enable) interleave(enable)
    for (auto &dest : destination)
    {
        //for (ui32 i = h_width; i > 0; --i, sp++, dp++)
        //dest += (s.beta() + s.lifting_coefficient() * (*source++ + *source)) >> s.epsilon();

        ++source;
    }
}

void reversible_forward_horizontal_refactored(const param_atk *atk,
                                              const line_buf *ldst,
                                              const line_buf *hdst,
                                              const line_buf *src,
                                              ui32 width,
                                              bool even)
{
    if (width > 1)
    {
        // combine both lsrc and hsrc into dst
        si32 *dph = hdst->i32;
        si32 *dpl = ldst->i32;
        si32 *sp = src->i32;
        ui32 w = width;
        if (!even)
        {
            *dph++ = *sp++;
            --w;
        }
        for (; w > 1; w -= 2)
        {
            *dpl++ = *sp++;
            *dph++ = *sp++;
        }
        if (w)
        {
            *dpl++ = *sp++;
            --w;
        }

        si32 *hp = hdst->i32, *lp = ldst->i32;
        ui32 l_width = (width + (even ? 1 : 0)) >> 1; // low pass
        ui32 h_width = (width + (even ? 0 : 1)) >> 1; // high pass
        ui32 num_steps = atk->get_num_steps();
        for (ui32 j = num_steps; j > 0; --j)
        {
            // first lifting step
            const lifting_step *s = atk->get_step(j - 1);
            const si32 a = s->rev.Aatk;
            const si32 b = s->rev.Batk;
            const ui8 e = s->rev.Eatk;

            // extension
            lp[-1] = lp[0];
            lp[l_width] = lp[l_width - 1];
            // lifting step
            const si32 *sp = lp + (even ? 1 : 0);
            si32 *dp = hp;
            if (a == 1)
            { // 5/3 update and any case with a == 1
                for (ui32 i = h_width; i > 0; --i, sp++, dp++)
                    *dp += (b + (sp[-1] + sp[0])) >> e;
            }
            else if (a == -1 && b == 1 && e == 1)
            { // 5/3 predict
                for (ui32 i = h_width; i > 0; --i, sp++, dp++)
                    *dp -= (sp[-1] + sp[0]) >> e;
            }
            else if (a == -1)
            { // any case with a == -1, which is not 5/3 predict
                for (ui32 i = h_width; i > 0; --i, sp++, dp++)
                    *dp += (b - (sp[-1] + sp[0])) >> e;
            }
            else
            {
                // general case
                for (ui32 i = h_width; i > 0; --i, sp++, dp++)
                    *dp += (b + a * (sp[-1] + sp[0])) >> e;
            }

            // swap buffers
            si32 *t = lp;
            lp = hp;
            hp = t;
            even = !even;
            ui32 w = l_width;
            l_width = h_width;
            h_width = w;
        }
    }
    else
    {
        if (even)
            ldst->i32[0] = src->i32[0];
        else
            hdst->i32[0] = src->i32[0] << 1;
    }
}


} // namespace reversible
} // namespace general
} // namespace wavelet
} // namespace openjph

#endif
