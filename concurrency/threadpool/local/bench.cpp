// bench.cpp

#include <benchmark/benchmark.h>

#include <chrono>
#include <thread>

#include "thread_pool_local.hpp"

static int64_t const MIN_WORKERS = 1;
static int64_t const MAX_WORKERS = std::thread::hardware_concurrency();

constexpr static auto const WORK_COUNT    = 100ul;
constexpr static auto const WORK_DURATION = 100ul;

static void BM_local_threadpool_throughput(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const n_threads = static_cast<std::size_t>(state.range(0)); //std::thread::hardware_concurrency() - 1;

    for (auto _ : state)
    {
        thread_pool_local pool{n_threads};

        auto const start = hr_clock::now();

        for (auto i = 0ul; i < WORK_COUNT; ++i)
        {
            pool.submit([]()
            { 
                for (auto j = 0ul; j < WORK_DURATION; ++j)
                {
                    // spin
                }
            });
        }

        // blocks until all work is complete
        pool.shutdown();

        auto const stop = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(static_cast<int64_t>(WORK_COUNT));
    }
}

BENCHMARK(BM_local_threadpool_throughput)->DenseRange(MIN_WORKERS, MAX_WORKERS)->UseManualTime();

BENCHMARK_MAIN();