#ifndef OJPH_TRANSFORM_H
#define OJPH_TRANSFORM_H

#pragma once

namespace openjph_algo {

    namespace wavelet {

        void init_wavelet_transform_functions();
/*
        namespace reversible {
            /////////////////////////////////////////////////////////////////////////
            extern void (*rev_vert_step)
            (const lifting_step* s, const line_buf* sig, const line_buf* other,
                const line_buf* aug, ui32 repeat, bool synthesis);

            /////////////////////////////////////////////////////////////////////////
            extern void (*rev_horz_ana)
            (const param_atk* atk, const line_buf* ldst, const line_buf* hdst,
                const line_buf* src, ui32 width, bool even);

            /////////////////////////////////////////////////////////////////////////
            extern void (*rev_horz_syn)
            (const param_atk* atk, const line_buf* dst, const line_buf* lsrc,
                const line_buf* hsrc, ui32 width, bool even);
        };

        namespace irreversible {
            /////////////////////////////////////////////////////////////////////////
            extern void (*irv_vert_step)
            (const lifting_step* s, const line_buf* sig, const line_buf* other,
                const line_buf* aug, ui32 repeat, bool synthesis);

            /////////////////////////////////////////////////////////////////////////
            extern void (*irv_vert_times_K)
            (float K, const line_buf* aug, ui32 repeat);

            /////////////////////////////////////////////////////////////////////////
            extern void (*irv_horz_ana)
            (const param_atk* atk, const line_buf* ldst, const line_buf* hdst,
                const line_buf* src, ui32 width, bool even);

            /////////////////////////////////////////////////////////////////////////
            extern void (*irv_horz_syn)
            (const param_atk* atk, const line_buf* dst, const line_buf* lsrc,
                const line_buf* hsrc, ui32 width, bool even);

        };
*/
    };

};
#endif
