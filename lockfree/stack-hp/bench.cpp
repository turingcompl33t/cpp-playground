// bench.cpp

#include <benchmark/benchmark.h>

#include <chrono>

#include "stack.hpp"

static void BM_stack_ping_pong(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const total_work = static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        stack<std::size_t> s{};

        auto start = hr_clock::now();

        for (auto i = 0ul; i < total_work; ++i)
        {
            s.push(i);
            auto r = s.pop();
        }

        auto stop = hr_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(static_cast<int64_t>(total_work));
    }
}

BENCHMARK(BM_stack_ping_pong)->RangeMultiplier(2)->Range(1 << 16, 1 << 22)->UseManualTime();

BENCHMARK_MAIN();