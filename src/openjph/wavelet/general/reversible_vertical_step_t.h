#ifndef OPENJPH_WAVELET_REVERSIBLE_VERTICAL_STEP_T_H
#define OPENJPH_WAVELET_REVERSIBLE_VERTICAL_STEP_T_H

#include <cassert>
#include <openjph/common.h>
//#include <cstddef>
#include <cstdio>
#include <cstring>
#include <openjph/wavelet/lifting_step.h>

#pragma once

namespace openjph
{

class line_buf;


namespace wavelet
{

using namespace openjph;
using namespace std;

union lifting_step;
class param_atk;

namespace general
{

namespace reversible
{

/**
 * @synthesis - true for inverse (decoding), false for forward (encoding)
 */
template <typename T>
void vertical_step(const lifting_step *s,
                   const T *signal1,
                   const T *signal2,
                   T *destination,
                   ui32 repeat,
                   bool synthesis)
{
    const T a = s->rev.Aatk;
    const T b = s->rev.Batk;
    const ui8 e = s->rev.Eatk;

    T *dst = destination;
    const T *src1 = signal1;
    const T *src2 = signal2;
    // The general definition of the wavelet in Part 2 is slightly
    // different to part 2, although they are mathematically equivalent
    // here, we identify the simpler form from Part 1 and employ them
    if (a == 1)
    { // 5/3 update and any case with a == 1
        if (synthesis)
            for (ui32 i = repeat; i > 0; --i)
                *dst++ -= (b + *src1++ + *src2++) >> e;
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
