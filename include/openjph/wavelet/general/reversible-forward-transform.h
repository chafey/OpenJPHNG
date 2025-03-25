#include <openjph/wavelet/reversible-forward-transform.h>

namespace openjph {
    namespace wavelet {
        namespace reversible {
            namespace general {

                class ForwardTransform : openjph::wavelet::reversible::ForwardTransform {
                    public:
                        virtual ~ForwardTransform();
                        virtual void VerticalStep(
                            const lifting_step* s,
                            const line_buf* sig,
                            const line_buf* other,
                            const line_buf* aug,
                            ui32 repeat,
                            bool synthesis) override;

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
