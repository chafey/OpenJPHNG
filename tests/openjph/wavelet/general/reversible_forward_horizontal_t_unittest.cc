#include "../../../../src/openjph/wavelet/general/reversible_forward_horizontal_t.h"
#include "../../../../src/openjph/wavelet/general/reversible_horizontal_ana_original.h"
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


TEST(OPENJPH_WaveletGeneralReversibleHorizontalT, CompareWithOriginalImplementation)
{
    const int srclength = 8;
    const int destlength = srclength / 2;
    ui32 width = srclength;
    bool even = true;

    param_atk atk;
    atk.init_rev53();
    si32 lowdestination[destlength + 1] = {0};
    line_buf ldst;
    ldst.wrap(lowdestination + 1, destlength, 0);
    line_buf hdst;
    si32 highdestination[destlength + 1] = {0};
    hdst.wrap(highdestination + 1, destlength, 0);
    line_buf src;
    si32 source[srclength] = {1, -3, 1, 6, 0, 2, 8, 0};
    src.wrap(source, srclength, 0);
    general::reversible::gen_rev_horz_ana32_original(&atk, &ldst, &hdst, &src, width, even);

    param_atk atk2;
    atk2.init_rev53();
    si32 lowdestination2[destlength + 1] = {0};
    line_buf ldst2;
    ldst2.wrap(lowdestination2 + 1, destlength, 0);
    line_buf hdst2;
    si32 highdestination2[destlength + 1] = {0};
    hdst2.wrap(highdestination2 + 1, destlength, 0);
    line_buf src2;
    si32 source2[srclength] = {1, -3, 1, 6, 0, 2, 8, 0};
    src2.wrap(source2, srclength, 0);

    general::reversible::reversible_forward_horizontal_refactored(&atk2, &ldst2, &hdst2, &src2, width, even);

    printArray<si32>(lowdestination, destlength);
    printArray<si32>(highdestination, destlength);

    EXPECT_TRUE(0 == std::memcmp(lowdestination, lowdestination2, destlength * sizeof(si32)));
    EXPECT_TRUE(0 == std::memcmp(highdestination, highdestination2, destlength * sizeof(si32)));
}
} // namespace