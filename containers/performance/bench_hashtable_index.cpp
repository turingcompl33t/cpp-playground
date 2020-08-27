// bench_hashtable_index.cpp

#include "benchmark/benchmark.h"

#include <chrono>
#include <vector>

constexpr static std::size_t const OPS_PER_ITER = 10'000;

constexpr static std::size_t const NOTIONAL_HT_SIZE = 128;

[[nodiscard]]
static std::vector<std::size_t> generate_dataset()
{
    std::vector<std::size_t> dataset{};

    dataset.reserve(OPS_PER_ITER);
    for (auto i = 0ul; i < OPS_PER_ITER; ++i)
    {
        dataset.push_back(i);
    }

    return dataset;
}

static void BM_bitwise_and(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const dataset = generate_dataset();

    for (auto _ : state)
    {
        auto const start = hr_clock::now();

        for (auto i : dataset)
        {
            benchmark::DoNotOptimize(i & (NOTIONAL_HT_SIZE - 1));
        }

        auto const stop = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<
            std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(OPS_PER_ITER);
    }
}

static void BM_integer_modulus(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const dataset = generate_dataset();

    for (auto _ : state)
    {
        auto const start = hr_clock::now();

        for (auto i : dataset)
        {
            benchmark::DoNotOptimize(i % NOTIONAL_HT_SIZE);
        }

        auto const stop = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<
            std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(OPS_PER_ITER);
    }
}

BENCHMARK(BM_bitwise_and)->UseManualTime();
BENCHMARK(BM_integer_modulus)->UseManualTime();

BENCHMARK_MAIN();