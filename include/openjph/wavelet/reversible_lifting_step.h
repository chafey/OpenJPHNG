#ifndef OPENJPH_WAVELET_REVERSIBLE_LIFTING_STEP_H
#define OPENJPH_WAVELET_REVERSIBLE_LIFTING_STEP_H

#include <cassert>
#pragma once

#include <openjph/common.h>

namespace openjph::wavelet
{

using namespace openjph;
using namespace std;

/**
 * struct to hold parameters for the reversible wavelet transform
 */
class ReversibleLiftingStep
{
public:
    ReversibleLiftingStep(si16 lifting_coefficient, si16 beta, ui8 epsilon)
        : lifting_coefficient_(lifting_coefficient), beta_(beta), epsilon_(epsilon)
    {
        assert(epsilon > 0);
        assert(lifting_coefficient != 0);
        // TODO: add additional parameter validation
    }

    [[nodiscard]]
    si16 lifting_coefficient() const
    {
        return lifting_coefficient_;
    }

    [[nodiscard]]
    si16 beta() const
    {
        return beta_;
    }

    [[nodiscard]]
    si16 epsilon() const
    {
        return epsilon_;
    }

private:
    si16 lifting_coefficient_; // lifting coefficient
    si16 beta_;                // the additive residue
    ui8 epsilon_;              // power of 2
};
} // namespace openjph::wavelet

#endif