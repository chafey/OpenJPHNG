#ifndef OPENJPH_WAVELET_H
#define OPENJPH_WAVELET_H

#include <openjph/common.h>
#include <cassert>
//#include <cstddef>
#include <cstdio>
#include <cstring>

#pragma once

namespace openjph {

    class line_buf;

    namespace wavelet {

        using namespace openjph;
        using namespace std;

        union lifting_step;
        class param_atk;


        void init_wavelet_transform_functions();


        namespace irreversible {
            /*
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
            */

            class ForwardTransform {
                public:
                    virtual void VerticalStep() = 0;
                    virtual void VerticalTimesK() = 0;
                    virtual void HorizontalAna() = 0;
            };

            class InverseTransform {
                public:
                    virtual void VerticalStep() = 0;
                    virtual void VerticalTimesK() = 0;
                    virtual void HorizonatlSyn() = 0;
            };
        }; // namespace irreversible
    }; // namespace wavelet
}; // namespace openjph
#endif
