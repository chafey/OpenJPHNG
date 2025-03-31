#ifndef OPENJPH_WAVELET_REVERSIBLE_HORIZONTAL_ANA_H
#define OPENJPH_WAVELET_REVERSIBLE_HORIZONTAL_ANA_H

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

void gen_rev_horz_ana32_original(const param_atk *atk,
                                 const line_buf *ldst,
                                 const line_buf *hdst,
                                 const line_buf *src,
                                 ui32 width,
                                 bool even);


void gen_rev_horz_ana64_original(const param_atk *atk,
                                 const line_buf *ldst,
                                 const line_buf *hdst,
                                 const line_buf *src,
                                 ui32 width,
                                 bool even);

}; // namespace reversible
}; // namespace general
}; // namespace wavelet
}; // namespace openjph
#endif
