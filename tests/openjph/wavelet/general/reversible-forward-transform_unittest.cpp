#include <gtest/gtest.h>
#include <openjph/wavelet/general/forward-reversible.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/param_atk.h>
#include <openjph/line_buf.h>

namespace {

    using namespace openjph;
    using namespace openjph::wavelet;

    TEST(WaveletGeneralReversibleForwardTransform, Positive) {
        openjph::wavelet::reversible::general::ForwardTransform xform;
        param_atk atk;
        line_buf ldst;
        line_buf hdst;
        line_buf src;
        ui32 width;
        bool even;
        
        xform.HorizontalAna(&atk, &ldst, &hdst, &src, width, even);
    }
}