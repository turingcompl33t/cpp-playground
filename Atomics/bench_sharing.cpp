// bench_sharing.cpp
//
// A benchmark comparing the performance implications for atomics when:
//  - The atomic is shared explicitly
//  - The atomic is shared implicitly (false sharing)
//  - The atomic is unshared (multiple values)

#include <benchmark/benchmark.h>

#include <chrono>
#include <atomic>
#include <thread>
#include <vector>

constexpr static std::size_t const TOTAL_WORK = 100'000;

static std::size_t unshared_worker(
    std::atomic<bool>& release_flag, 
    std::size_t const  work_per_thread)
{
    while (!release_flag.load())
    {
        std::this_thread::yield();
    }

    std::atomic<std::size_t> local_count{0};
    for (auto i = 0ul; i < work_per_thread; ++i)
    {
        local_count.fetch_add(1);
    }

    // prevent optimization??
    return local_count.load();
}

// benchmark atomic increments for unshared variables
static void BM_unshared(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const n_threads       = static_cast<std::size_t>(state.range(0));
    auto const work_per_thread = TOTAL_WORK / n_threads;

    for (auto _ : state)
    {
        std::atomic<bool> release_flag{false};

        std::vector<std::thread> threads{};
        for (auto i = 0ul; i < n_threads; ++i)
        {
            threads.emplace_back(
                unshared_worker, 
                std::ref(release_flag), 
                work_per_thread);
        }

        auto const start = hr_clock::now();

        release_flag.store(true);

        for (auto& t : threads)
        {
            t.join();
        }

        auto const end = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        state.SetIterationTime(elapsed.count());
    }
}

static void shared_worker(
    std::atomic<bool>&        release_flag,
    std::atomic<std::size_t>& shared_count, 
    std::size_t const         work_per_thread)
{
    while (!release_flag.load())
    {
        std::this_thread::yield();
    }

    for (auto i = 0ul; i < work_per_thread; ++i)
    {
        shared_count.fetch_add(1);
    }
}

// benchmark atomic increments for explicitly shared variable
static void BM_shared(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const n_threads       = static_cast<std::size_t>(state.range(0));
    auto const work_per_thread = TOTAL_WORK / n_threads;

    for (auto _ : state)
    {
        std::atomic<bool> release_flag{false};
        std::atomic<std::size_t> shared_count{0};

        std::vector<std::thread> threads{};
        for (auto i = 0ul; i < n_threads; ++i)
        {
            threads.emplace_back(
                shared_worker, 
                std::ref(release_flag), 
                std::ref(shared_count), 
                work_per_thread);
        }

        auto const start = hr_clock::now();

        release_flag.store(true);

        for (auto& t : threads)
        {
            t.join();
        }

        auto const end = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        state.SetIterationTime(elapsed.count());
    }
}

BENCHMARK(BM_unshared)->RangeMultiplier(2)->Range(2, 32)->UseManualTime();
BENCHMARK(BM_shared)->RangeMultiplier(2)->Range(2, 32)->UseManualTime();

BENCHMARK_MAIN();