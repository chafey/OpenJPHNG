#pragma once
#include <openjph/common.h>
#include <span>

namespace openjph
{

namespace wavelet
{
using namespace openjph;
using namespace wavelet;

class ReversibleLiftingStep;

namespace neon
{
namespace reversible
{


/////////////////////////////////////////////////////////////////////////
void neon_forward_vertical_step(const ReversibleLiftingStep &s,
                                const std::span<const si32> &upper_line,
                                const std::span<const si32> &lower_line,
                                const std::span<si32> &destination);
} // namespace reversible
} // namespace neon
} // namespace wavelet
} // namespace openjph
