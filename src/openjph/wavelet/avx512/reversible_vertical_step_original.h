#pragma once
#include <openjph/common.h>

namespace openjph
{
class line_buf;

namespace wavelet
{
using namespace openjph;
using namespace wavelet;
union lifting_step;

namespace avx512
{
namespace reversible
{


/////////////////////////////////////////////////////////////////////////
void avx512_rev_vert_step32_original(const lifting_step *s,
                                     const line_buf *sig,
                                     const line_buf *other,
                                     const line_buf *aug,
                                     ui32 repeat,
                                     bool synthesis);
} // namespace reversible
} // namespace avx512
} // namespace wavelet
} // namespace openjph
