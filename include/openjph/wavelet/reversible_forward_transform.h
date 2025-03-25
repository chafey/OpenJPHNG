#ifndef OPENJPH_WAVELET_FORWARD_TRANSFORM_H
#define OPENJPH_WAVELET_FORWARD_TRANSFORM_H

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

        namespace reversible {
            // TODO: See if we can use the same interface for both reversible and irreversible
            class ForwardTransform {
                public:
                    virtual ~ForwardTransform() {};
                    // TODO: pass parameters by reference, not pointer
                    virtual void VerticalStep(
                        const lifting_step* s,
                        const line_buf* sig,
                        const line_buf* other,
                        const line_buf* aug,
                        ui32 repeat,
                        bool synthesis) = 0;

                    // TODO: pass parameters by reference, not pointer
                    virtual void HorizontalAna(
                        const param_atk* atk,
                        const line_buf* ldst,
                        const line_buf* hdst,
                        const line_buf* src,
                        ui32 width,
                        bool even) = 0;
            };
        }; // namespace reversible
    }; // namespace wavelet
}; // namespace openjph
#endif
