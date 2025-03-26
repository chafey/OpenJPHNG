#ifndef OPENJPH_WAVELET_REVERSIBLE_VERTICAL_STEP_H
#define OPENJPH_WAVELET_REVERSIBLE_VERTICAL_STEP_H

#include <cassert>
#include <openjph/common.h>
//#include <cstddef>
#include <cstdio>
#include <cstring>

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
void gen_rev_vert_step32(const lifting_step *s,
                         const line_buf *sig,
                         const line_buf *other,
                         const line_buf *aug,
                         ui32 repeat,
                         bool synthesis);

void gen_rev_vert_step64(const lifting_step *s,
                         const line_buf *sig,
                         const line_buf *other,
                         const line_buf *aug,
                         ui32 repeat,
                         bool synthesis);

}; // namespace reversible
}; // namespace general
}; // namespace wavelet
}; // namespace openjph
#endif
