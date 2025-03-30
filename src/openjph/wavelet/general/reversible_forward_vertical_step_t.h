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

/**
 * The general case for wavelet forward vertical step transform
 */
template <typename T>
void reversible_forward_vertical_step_general(const ReversibleLiftingStep &s,
                                              const std::span<const T> &upper_line,
                                              const std::span<const T> &lower_line,
                                              const std::span<T> &destination)
{
    assert(upper_line.size() >= destination.size());
    assert(lower_line.size() >= destination.size());

    auto lower_line_iterator = std::cbegin(lower_line);
    auto upper_line_iterator = std::cbegin(upper_line);
#pragma clang loop vectorize(enable) interleave(enable)
    for (auto &dest : destination)
    {
        dest += (s.beta() + s.lifting_coefficient() * (*upper_line_iterator + *lower_line_iterator)) >> s.epsilon();
        ++upper_line_iterator;
        ++lower_line_iterator;
    }
}
/**
 * Optimized case for wavelet forward vertical step transform when lifting_coefficient =1, beta = 0, epsilon = 1
 */
template <typename T>
void reversible_forward_vertical_step_c1_b0_e1(const std::span<const T> &upper_line,
                                               const std::span<const T> &lower_line,
                                               const std::span<T> &destination)
{
    assert(upper_line.size() >= destination.size());
    assert(lower_line.size() >= destination.size());

    auto lower_line_iterator = std::cbegin(lower_line);
    auto upper_line_iterator = std::cbegin(upper_line);
#pragma clang loop vectorize(enable) interleave(enable)
    for (auto &dest : destination)
    {
        dest += (*upper_line_iterator + *lower_line_iterator) >> 1;
        ++upper_line_iterator;
        ++lower_line_iterator;
    }
}

/**
 * Optimized case for wavelet forward vertical step transform when lifting_coefficient =-1, beta = 1, epsilon = 1
 */
template <typename T>
void reversible_forward_vertical_step_cn1_b1_e1(const std::span<const T> &upper_line,
                                                const std::span<const T> &lower_line,
                                                const std::span<T> &destination)
{
    assert(upper_line.size() >= destination.size());
    assert(lower_line.size() >= destination.size());

    auto lower_line_iterator = std::cbegin(lower_line);
    auto upper_line_iterator = std::cbegin(upper_line);
#pragma clang loop vectorize(enable) interleave(enable)
    for (auto &dest : destination)
    {
        dest -= (*upper_line_iterator + *lower_line_iterator) >> 1;
        ++upper_line_iterator;
        ++lower_line_iterator;
    }
}
/**
 * Optimized case for wavelet forward vertical step transform when lifting_coefficient =-1
 */
template <typename T>
void reversible_forward_vertical_step_cn1(si16 beta,
                                          ui8 epsilon,
                                          const std::span<const T> &upper_line,
                                          const std::span<const T> &lower_line,
                                          const std::span<T> &destination)
{
    assert(upper_line.size() >= destination.size());
    assert(lower_line.size() >= destination.size());

    auto lower_line_iterator = std::cbegin(lower_line);
    auto upper_line_iterator = std::cbegin(upper_line);
#pragma clang loop vectorize(enable) interleave(enable)
    for (auto &dest : destination)
    {
        dest += (beta - (*upper_line_iterator + *lower_line_iterator)) >> epsilon;
        ++upper_line_iterator;
        ++lower_line_iterator;
    }
}

/**
 * Performs the reversible wavelet forward vertical step.  
 * NOTE: Each of the paths in this function is an optiization for identity
 *       values of the lifting step properties 
 */
template <typename T>
void reversible_forward_vertical_step_refactored(const ReversibleLiftingStep &s,
                                                 const std::span<const T> &upper_line,
                                                 const std::span<const T> &lower_line,
                                                 const std::span<T> &destination)
{
    assert(upper_line.size() >= destination.size());
    assert(lower_line.size() >= destination.size());

    if (s.lifting_coefficient() == 1 && s.beta() == 0 && s.epsilon() == 1)
    {
        reversible_forward_vertical_step_c1_b0_e1(upper_line, lower_line, destination);
    }
    else if (s.lifting_coefficient() == -1)
    {
        if (s.beta() == 1 && s.epsilon() == 1)
        {
            reversible_forward_vertical_step_cn1_b1_e1(upper_line, lower_line, destination);
        }
        else
        {
            reversible_forward_vertical_step_cn1(s.beta(), s.epsilon(), upper_line, lower_line, destination);
        }
    }
    else
    {
        reversible_forward_vertical_step_general(s, upper_line, lower_line, destination);
    }
}


}; // namespace reversible
}; // namespace general
}; // namespace wavelet
}; // namespace openjph
#endif
