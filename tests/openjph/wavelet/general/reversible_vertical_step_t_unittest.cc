#include "../../../../src/openjph/wavelet/general/reversible_forward_vertical_step_t.h"
#include "../../../../src/openjph/wavelet/general/reversible_vertical_step_original.h"
#include <gtest/gtest.h>
#include <openjph/line_buf.h>
#include <openjph/wavelet/general/reversible_forward_transform.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/param_atk.h>
#include <openjph/wavelet/reversible_lifting_step.h>
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


TEST(OPENJPH_WaveletGeneralReversibleVerticalStepT, CompareWithOriginalImplementation)
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
    bool synthesis = false;
    general::reversible::gen_rev_vert_step32_original(&liftingStep, &sig, &oth, &aug, repeat, synthesis);
    printArray<si32>(augb, length);

    ReversibleLiftingStep reversible_lifting_step(1, 0, 1);
    si32 upper_line_buffer[length] = {10, -20, 5, -15};
    span<const si32> upper_line(upper_line_buffer, length);
    si32 lower_line_buffer[length] = {-5, -6, -7, -8};
    span<const si32> lower_line(lower_line_buffer, length);
    si32 destination_buffer[length] = {0};
    span<si32> destination(destination_buffer, length);

    openjph::wavelet::general::reversible::reversible_forward_vertical_step_refactored<si32>(reversible_lifting_step,
                                                                                             upper_line,
                                                                                             lower_line,
                                                                                             destination);

    /*general::reversible::forward_vertical_step_optimized<si32>(reversible_lifting_step,
                                                               upper_line,
                                                               lower_line,
                                                               destination);
    */
    printArray<si32>(destination_buffer, length);

    EXPECT_TRUE(0 == std::memcmp(augb, destination_buffer, length * sizeof(si32)));
}

// TODO: Add unit tests for each optimization path in forward_vertical_step_optimized
// TODO: Add unit tests for edge cases (max values?)
// TODO: Add unit tests for negative cases (destination length > line length)


} // namespace