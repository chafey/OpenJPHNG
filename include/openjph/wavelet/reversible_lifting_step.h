#ifndef OPENJPH_WAVELET_REVERSIBLE_LIFTING_STEP_H
#define OPENJPH_WAVELET_REVERSIBLE_LIFTING_STEP_H

#pragma once

#include <openjph/common.h>

namespace openjph::wavelet
{

using namespace openjph;
using namespace std;

/**
 * struct to hold parameters for the reversible wavelet transform
 */
struct ReversibleLiftingStep
{
    si16 lifting_coefficient; // lifting coefficient
    si16 beta;                // the additive residue
    ui8 epsilon;              // power of 2
};
} // namespace openjph::wavelet

#endif