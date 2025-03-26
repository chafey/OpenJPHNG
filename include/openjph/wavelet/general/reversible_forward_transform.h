#ifndef OPENJPH_WAVELET_GENERAL_REVERSIBLE_FORWARD_TRANSFORM_H
#define OPENJPH_WAVELET_GENERAL_REVERSIBLE_FORWARD_TRANSFORM_H

#pragma once

#include <openjph/wavelet/reversible_forward_transform.h>

namespace openjph {
    namespace wavelet {
        namespace general {
            namespace reversible {

                class ForwardTransform : openjph::wavelet::reversible::ForwardTransform {
                    public:
                        virtual ~ForwardTransform();
                        // TODO: Pass by reference not pointer
                        // TODO: try to reduce parameter count
                        // TODO: document each parameter
                        virtual void VerticalStep(
                            const lifting_step* s,
                            const line_buf* sig,
                            const line_buf* other,
                            const line_buf* aug,
                            ui32 repeat,
                            bool synthesis) override;

                        // TODO: Pass by reference not pointer
                        // TODO: try to reduce parameter count
                        // TODO: document each parameter
                        // TODO: what does Ana stand for?  Replace with more descriptive name
                        virtual void HorizontalAna(
                            const param_atk* atk,
                            const line_buf* ldst,
                            const line_buf* hdst,
                            const line_buf* src,
                            ui32 width,
                            bool even) override;

                };
            }
        }
    }


} // namespace openjph::wavelet::reversible::general
#endif // OPENJPH_WAVELET_GENERAL_REVERSIBLE_FORWARD_TRANSFORM_H
