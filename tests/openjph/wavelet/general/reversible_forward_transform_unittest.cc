#include <gtest/gtest.h>
#include <openjph/wavelet/general/reversible_forward_transform.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/param_atk.h>
#include <openjph/line_buf.h>

namespace {

    using namespace openjph;
    using namespace openjph::wavelet;

    TEST(WaveletGeneralReversibleForwardTransform, HappyPath) {
        openjph::wavelet::reversible::general::ForwardTransform xform;
        /*
        // TODO: Fill these parameters out for a simple happy path
        lifting_step s;
        param_atk atk;
        line_buf ldst;
        line_buf hdst;
        line_buf src;
        ui32 repeat;
        bool synthesis;
        xform.VerticalStep(&s, &ldst, &hdst, &src, repeat, synthesis) ; 

        ui32 width;
        bool even;
        xform.HorizontalAna(&atk, &ldst, &hdst, &src, width, even);
        */
    }

    // TODO: add more tests
    TEST(WaveletGeneralReversibleForwardTransform, InvalidParameter) {
    }
}