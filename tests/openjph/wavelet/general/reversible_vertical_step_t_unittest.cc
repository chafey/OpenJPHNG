#include "../../../../src/openjph/wavelet/general/reversible_vertical_step.h"
#include "../../../../src/openjph/wavelet/general/reversible_vertical_step_t.h"
#include <gtest/gtest.h>
#include <openjph/line_buf.h>
#include <openjph/wavelet/general/reversible_forward_transform.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/param_atk.h>
#include <span>

namespace
{

using namespace openjph;
using namespace openjph::wavelet;

template <typename T>
void printArray(T *array, size_t length)
{
    for (size_t index = 0; index < length; index++)
    {
        cout << array[index] << " ";
    }
    cout << endl;
}

TEST(WaveletGeneralReversibleVerticalStepT, HappyPath)
{
    lifting_step liftingStep;
    const int length = 4;
    si32 signal1[length] = {1, 2, 3, 4};
    span<si32> signal1Span(signal1, length);
    si32 signal2[length] = {-5, -6, -7, -8};
    span<si32> signal2Span(signal2, length);
    si32 destination[length] = {0};
    span<si32> destinationSpan(destination, length);
    ui32 repeat = 32;
    bool synthesis = true;
    general::reversible::vertical_step<si32>(liftingStep, signal1Span, signal2Span, destinationSpan, synthesis);
}

TEST(WaveletGeneralReversibleVerticalStepT, CompareWithOriginalImplementation)
{
    lifting_step liftingStep;
    liftingStep.rev.Aatk = 1;
    liftingStep.rev.Batk = 0;
    liftingStep.rev.Eatk = 1;

    const int length = 4;
    si32 sigb[length] = {10, -20, 5, -15};
    line_buf sig;
    sig.wrap(sigb, length, 0);
    si32 othb[length] = {-5, -6, -7, -8};
    line_buf oth;
    oth.wrap(othb, length, 0);
    si32 augb[length] = {0};
    line_buf aug;
    aug.wrap(augb, length, 0);
    ui32 repeat = length;
    bool synthesis = true;
    general::reversible::gen_rev_vert_step32(&liftingStep, &sig, &oth, &aug, repeat, synthesis);
    printArray<si32>(augb, length);

    si32 signal1[length] = {10, -20, 5, -15};
    span<si32> signal1Span(signal1, length);
    si32 signal2[length] = {-5, -6, -7, -8};
    span<si32> signal2Span(signal2, length);
    si32 destination[length] = {0};
    span<si32> destinationSpan(destination, length);
    general::reversible::vertical_step<si32>(liftingStep, signal1Span, signal2Span, destinationSpan, synthesis);
    printArray<si32>(destination, length);

    EXPECT_TRUE(0 == std::memcmp(augb, destination, length * sizeof(si32)));
}
} // namespace