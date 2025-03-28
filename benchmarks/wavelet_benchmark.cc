#include "../../../../src/openjph/wavelet/general/reversible_forward_vertical_step_t.h"
#include "../../../../src/openjph/wavelet/general/reversible_vertical_step.h"
#include "../../../../src/openjph/wavelet/avx512/reversible_forward_vertical_step.h"
#include <benchmark/benchmark.h>
#include <gtest/gtest.h>
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
si32 upper_line_buffer[buffer_length] = {0};
si32 lower_line_buffer[buffer_length] = {0};
si32 destination_buffer[buffer_length] = {0};

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
    bool synthesis = true;


    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        general::reversible::gen_rev_vert_step32(&liftingStep,
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
        general::reversible::forward_vertical_step<si32>(reversible_lifting_step, upper_line, lower_line, destination);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepRefactored);

void BW_ForwardVerticalStepOptimized(benchmark::State &state)
{
    const int length = buffer_length;
    ReversibleLiftingStep reversible_lifting_step(1, 0, 1);
    span<const si32> upper_line(upper_line_buffer, length);
    span<const si32> lower_line(lower_line_buffer, length);
    span<si32> destination(destination_buffer, length);
    resetFixtures();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        general::reversible::forward_vertical_step_optimized<si32>(reversible_lifting_step,
                                                                   upper_line,
                                                                   lower_line,
                                                                   destination);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepOptimized);

void BW_ForwardVerticalStepAVX512(benchmark::State &state)
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
    bool synthesis = true;


    for (auto _ : state)
    {
        benchmark::DoNotOptimize(destination_buffer);
        openjph::wavelet::avx512::reversible::avx512_rev_vert_step32(&liftingStep,
                                                 &upper_line,
                                                 &lower_line,
                                                 &destination,
                                                 repeat,
                                                 synthesis);
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * length * sizeof(si32));
}
BENCHMARK(BW_ForwardVerticalStepAVX512);


} // namespace

BENCHMARK_MAIN();