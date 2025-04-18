#include "../src/openjph/wavelet/avx512/reversible_forward_vertical_step.h"
#include "../src/openjph/wavelet/avx512/reversible_vertical_step_original.h"
#include "../src/openjph/wavelet/general/reversible_forward_vertical_step_t.h"
#include "../src/openjph/wavelet/general/reversible_vertical_step_original.h"
#include "../src/openjph/wavelet/neon/reversible_forward_vertical_step.h"
#include <benchmark/benchmark.h>
#include <openjph/line_buf.h>
#include <openjph/wavelet/general/reversible_forward_transform.h>
#include <openjph/wavelet/lifting_step.h>
#include <openjph/wavelet/param_atk.h>
#include <openjph/wavelet/reversible_lifting_step.h>
#include <span>

namespace
{
using namespace openjph;
using namespace openjph::wavelet;

// TODO: set this to the common buffer length or change to a range of values to test different ones
const int buffer_length = 4096;
alignas(64) si32 upper_line_buffer[buffer_length] = {0};
alignas(64) si32 lower_line_buffer[buffer_length] = {0};
alignas(64) si32 destination_buffer[buffer_length] = {0};

void resetFixtures()
{
    memset(destination_buffer, 0, buffer_length * sizeof(si32));
    for (size_t i = 0; i < buffer_length; i++)
    {
        upper_line_buffer[i] = i;
        lower_line_buffer[i] = i * 2;
    }
}


void BW_ForwardVerticalStepOriginal(benchmark::State &state)
{
    const int length = buffer_length;
    ReversibleLiftingStep reversible_lifting_step(1, 0, 1);
    line_buf upper_line;
    upper_line.wrap(upper_line_buffer, buffer_length, 0);
    line_buf lower_line;
    lower_line.wrap(upper_line_buffer, buffer_length, 0);
    line_buf destination;
    destination.wrap(destination_buffer, buffer_length, 0);
    lifting_step liftingStep;
    liftingStep.rev.Aatk = 1;
    liftingStep.rev.Batk = 0;
    liftingStep.rev.Eatk = 1;

    ui32 repeat = buffer_length;
    bool synthesis = false;


    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        general::reversible::gen_rev_vert_step32_original(&liftingStep,
                                                          &upper_line,
                                                          &lower_line,
                                                          &destination,
                                                          repeat,
                                                          synthesis);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepOriginal);

void BW_ForwardVerticalStepRefactored(benchmark::State &state)
{
    const int length = buffer_length;
    ReversibleLiftingStep reversible_lifting_step(1, 0, 1);
    std::span<const si32> upper_line(upper_line_buffer, length);
    std::span<const si32> lower_line(lower_line_buffer, length);
    std::span<si32> destination(destination_buffer, length);
    resetFixtures();
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        general::reversible::reversible_forward_vertical_step_refactored<si32>(reversible_lifting_step,
                                                                               upper_line,
                                                                               lower_line,
                                                                               destination);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepRefactored);

#ifdef __x86_64__
void BW_ForwardVerticalStepAVX512Original(benchmark::State &state)
{
    const int length = buffer_length;
    ReversibleLiftingStep reversible_lifting_step(1, 0, 1);
    line_buf upper_line;
    upper_line.wrap(upper_line_buffer, buffer_length, 0);
    line_buf lower_line;
    lower_line.wrap(upper_line_buffer, buffer_length, 0);
    line_buf destination;
    destination.wrap(destination_buffer, buffer_length, 0);
    lifting_step liftingStep;
    liftingStep.rev.Aatk = 1;
    liftingStep.rev.Batk = 0;
    liftingStep.rev.Eatk = 1;

    ui32 repeat = buffer_length;
    bool synthesis = false;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        openjph::wavelet::avx512::reversible::avx512_rev_vert_step32_original(&liftingStep,
                                                                              &upper_line,
                                                                              &lower_line,
                                                                              &destination,
                                                                              repeat,
                                                                              synthesis);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepAVX512Original);

void BW_ForwardVerticalStepAVX512Refactored(benchmark::State &state)
{
    const int length = buffer_length;
    ReversibleLiftingStep reversible_lifting_step(1, 0, 1);
    std::span<const si32> upper_line(upper_line_buffer, length);
    std::span<const si32> lower_line(lower_line_buffer, length);
    std::span<si32> destination(destination_buffer, length);
    resetFixtures();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        openjph::wavelet::avx512::reversible::avx512_reversible_forward_vertial_step_refactored(reversible_lifting_step,
                                                                                                upper_line,
                                                                                                lower_line,
                                                                                                destination);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepAVX512Refactored);

void BW_ForwardVerticalStepAVX512C1B0E1(benchmark::State &state)
{
    const int length = buffer_length;
    std::span<const si32> upper_line(upper_line_buffer, length);
    std::span<const si32> lower_line(lower_line_buffer, length);
    std::span<si32> destination(destination_buffer, length);
    resetFixtures();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        openjph::wavelet::avx512::reversible::avx512_reversible_forward_vertial_step_c1_b0_e1(upper_line,
                                                                                              lower_line,
                                                                                              destination);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepAVX512C1B0E1);

void BW_ForwardVerticalStepAVX512CN1B1E1(benchmark::State &state)
{
    const int length = buffer_length;
    std::span<const si32> upper_line(upper_line_buffer, length);
    std::span<const si32> lower_line(lower_line_buffer, length);
    std::span<si32> destination(destination_buffer, length);
    resetFixtures();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        openjph::wavelet::avx512::reversible::avx512_reversible_forward_vertial_step_cn1_b1_e1(upper_line,
                                                                                               lower_line,
                                                                                               destination);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepAVX512CN1B1E1);

void BW_ForwardVerticalStepAVX512CN1(benchmark::State &state)
{
    const int length = buffer_length;
    std::span<const si32> upper_line(upper_line_buffer, length);
    std::span<const si32> lower_line(lower_line_buffer, length);
    std::span<si32> destination(destination_buffer, length);
    resetFixtures();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        openjph::wavelet::avx512::reversible::avx512_reversible_forward_vertial_step_cn1(2,
                                                                                         1,
                                                                                         upper_line,
                                                                                         lower_line,
                                                                                         destination);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepAVX512CN1);


void BW_ForwardVerticalStepAVX512General(benchmark::State &state)
{
    const int length = buffer_length;
    ReversibleLiftingStep reversible_lifting_step(1, 0, 1);
    std::span<const si32> upper_line(upper_line_buffer, length);
    std::span<const si32> lower_line(lower_line_buffer, length);
    std::span<si32> destination(destination_buffer, length);
    resetFixtures();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        openjph::wavelet::avx512::reversible::avx512_reversible_forward_vertial_step_general(reversible_lifting_step,
                                                                                             upper_line,
                                                                                             lower_line,
                                                                                             destination);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepAVX512General);


#endif

#ifdef __ARM_NEON
void BW_ForwardVerticalStepNEON(benchmark::State &state)
{
    const int length = buffer_length;
    ReversibleLiftingStep reversible_lifting_step(1, 0, 1);
    std::span<const si32> upper_line(upper_line_buffer, length);
    std::span<const si32> lower_line(lower_line_buffer, length);
    std::span<si32> destination(destination_buffer, length);
    resetFixtures();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        openjph::wavelet::neon::reversible::neon_forward_vertical_step(reversible_lifting_step,
                                                                       upper_line,
                                                                       lower_line,
                                                                       destination);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepNEON);
#endif

} // namespace

BENCHMARK_MAIN();