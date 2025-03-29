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

namespace avx512
{
namespace reversible
{


/////////////////////////////////////////////////////////////////////////
void avx512_reversible_forward_vertial_step_refactored(const ReversibleLiftingStep &s,
                                                       const std::span<const si32> &upper_line,
                                                       const std::span<const si32> &lower_line,
                                                       const std::span<si32> &destination);

void avx512_reversible_forward_vertial_step_general(const ReversibleLiftingStep &s,
                                                    const std::span<const si32> &upper_line,
                                                    const std::span<const si32> &lower_line,
                                                    const std::span<si32> &destination);
void avx512_reversible_forward_vertial_step_c1_b0_e1(const std::span<const si32> &upper_line,
                                                     const std::span<const si32> &lower_line,
                                                     const std::span<si32> &destination);
void avx512_reversible_forward_vertial_step_cn1_b1_e1(const std::span<const si32> &upper_line,
                                                      const std::span<const si32> &lower_line,
                                                      const std::span<si32> &destination);
void avx512_reversible_forward_vertial_step_cn1(si16 beta,
                                                ui8 epsilon,
                                                const std::span<const si32> &upper_line,
                                                const std::span<const si32> &lower_line,
                                                const std::span<si32> &destination);
} // namespace reversible
} // namespace avx512
} // namespace wavelet
} // namespace openjph
