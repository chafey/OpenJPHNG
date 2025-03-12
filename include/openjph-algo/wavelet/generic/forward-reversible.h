#include <openjph-algo/openjph-algo-wavelet.h>

namespace openjph_algo::wavelet::reversible::generic {

    class ForwardTransform : openjph_algo::wavelet::reversible::ForwardTransform {
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

} // namespace openjph_algo::wavelet::reversible::generic
