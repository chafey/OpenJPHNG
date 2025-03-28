#ifndef OPENJPH_WAVELET_REVERSIBLE_FORWARD_VERTICAL_STEP_T_H
#define OPENJPH_WAVELET_REVERSIBLE_FORWARD_VERTICAL_STEP_T_H

#include <cassert>
#include <openjph/common.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/reversible_lifting_step.h>
#include <span>
#pragma once

namespace openjph
{

namespace wavelet
{

using namespace openjph;
using namespace std;

union lifting_step;

namespace general
{

namespace reversible
{
// The general definition of the wavelet in Part 2 is slightly
// different to part 2, although they are mathematically equivalent
// here, we identify the simpler form from Part 1 and employ them
template <typename T>
void forward_vertical_step_general(const ReversibleLiftingStep &s,
                                   const std::span<const T> &upper_line,
                                   const std::span<const T> &lower_line,
                                   const std::span<T> &destination)
{
    assert(upper_line.size() >= destination.size());
    assert(lower_line.size() >= destination.size());

    // Note - using iterators and range for can result in higher performance due to compiler optimizations
    auto lower_line_iterator = std::cbegin(lower_line);
    auto upper_line_iterator = std::cbegin(upper_line);
    //#pragma clang loop vectorize(enable) interleave(enable)
    for (auto &dest : destination)
    {
        // TODO: can we change += to =?
        dest += (s.beta() + s.lifting_coefficient() * (*upper_line_iterator + *lower_line_iterator)) >> s.epsilon();
        ++upper_line_iterator;
        ++lower_line_iterator;
    }
}

/**
 */
// The general definition of the wavelet in Part 2 is slightly
// different to part 2, although they are mathematically equivalent
// here, we identify the simpler form from Part 1 and employ them
template <typename T>
void forward_vertical_step_optimized(const ReversibleLiftingStep &s,
                                     const std::span<const T> &upper_line,
                                     const std::span<const T> &lower_line,
                                     const std::span<T> &destination)
{
    assert(upper_line.size() >= destination.size());
    assert(lower_line.size() >= destination.size());
    const T lifting_coefficient = s.lifting_coefficient();
    const T beta = s.beta();
    const ui8 epsilon = s.epsilon();

    auto lower_line_iterator = std::cbegin(lower_line);
    auto upper_line_iterator = std::cbegin(upper_line);
    if (lifting_coefficient == 1)
    {
        for (auto &dest : destination)
        {
            // TODO: can we change += to =?
            dest += (beta + (*upper_line_iterator + *lower_line_iterator)) >> epsilon;
            ++upper_line_iterator;
            ++lower_line_iterator;
        }
    }
    else if (lifting_coefficient == -1 && beta == 1 && epsilon == 1)
    {
        // 5/3 predict
        for (auto &dest : destination)
        {
            // TODO: can we change += to =?
            dest += (*upper_line_iterator + *lower_line_iterator) >> epsilon;
            ++upper_line_iterator;
            ++lower_line_iterator;
        }
    }
    else if (lifting_coefficient == -1)
    {
        // any case with a == -1, which is not 5/3 predict
        for (auto &dest : destination)
        {
            // TODO: can we change += to =?
            dest += (beta - (*upper_line_iterator + *lower_line_iterator)) >> epsilon;
            ++upper_line_iterator;
            ++lower_line_iterator;
        }
    }
    else
    {
        // general case
        forward_vertical_step_general<T>(s, upper_line, lower_line, destination);
    }
}

}; // namespace reversible
}; // namespace general
}; // namespace wavelet
}; // namespace openjph
#endif
