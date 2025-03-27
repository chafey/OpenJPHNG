#ifndef OPENJPH_WAVELET_REVERSIBLE_VERTICAL_STEP_T_H
#define OPENJPH_WAVELET_REVERSIBLE_VERTICAL_STEP_T_H

#include <cassert>
#include <openjph/common.h>
//#include <cstddef>
#include <cstdio>
#include <cstring>
#include <openjph/wavelet/lifting_step.h>
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

/**
 * @synthesis - true for inverse (decoding), false for forward (encoding)
 */
template <typename T>
void vertical_step(const lifting_step &s,
                   const span<T> &signal1,
                   const span<T> &signal2,
                   span<T> &destination,
                   bool synthesis)
{
    //printf("%zu %zu %zu\n", signal1.size(), signal2.size(), destination.size());
    assert(signal1.size() == signal2.size());
    assert(signal1.size() == destination.size());
    const T a = s.rev.Aatk;
    const T b = s.rev.Batk;
    const ui8 e = s.rev.Eatk;
    const size_t repeat = signal1.size();

    T *dst = destination.data();
    const T *src1 = signal1.data();
    const T *src2 = signal2.data();
    // The general definition of the wavelet in Part 2 is slightly
    // different to part 2, although they are mathematically equivalent
    // here, we identify the simpler form from Part 1 and employ them
    if (a == 1)
    { // 5/3 update and any case with a == 1
        if (synthesis)
        {
            span<si32>::iterator sig2Iterator = signal2.begin();
            span<si32>::iterator destIterator = destination.begin();
            for (auto &s1 : signal1)
            {
                *destIterator++ -= (b + s1 + *sig2Iterator++) >> e;
            }
        }
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (b + *src1++ + *src2++) >> e;
    }
    else if (a == -1 && b == 1 && e == 1)
    { // 5/3 predict
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (*src1++ + *src2++) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (*src1++ + *src2++) >> e;
    }
    else if (a == -1)
    { // any case with a == -1, which is not 5/3 predict
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (b - (*src1++ + *src2++)) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (b - (*src1++ + *src2++)) >> e;
    }
    else
    { // general case
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (b + a * (*src1++ + *src2++)) >> e;
        else
            for (ui32 i = repeat; i > 0; --i)
                *dst++ += (b + a * (*src1++ + *src2++)) >> e;
    }
}

}; // namespace reversible
}; // namespace general
}; // namespace wavelet
}; // namespace openjph
#endif
