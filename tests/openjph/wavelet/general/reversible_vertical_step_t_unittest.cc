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
    si32 signal[length] = {1, 2, 3, 4};
    si32 other[length] = {-5, -6, -7, -8};
    si32 aug[length] = {0};
    ui32 repeat = 32;
    bool synthesis = true;
    general::reversible::vertical_step<si32>(&liftingStep, signal, other, aug, repeat, synthesis);
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

    si32 signal[length] = {10, -20, 5, -15};
    si32 other[length] = {-5, -6, -7, -8};
    si32 augz[length] = {0};
    general::reversible::vertical_step<si32>(&liftingStep, signal, other, augz, repeat, synthesis);
    printArray<si32>(augz, length);

    EXPECT_TRUE(0 == std::memcmp(augb, augz, length * sizeof(si32)));
}
} // namespace