// bench_atomic_vs_mutex.cpp
//
// A benchmark comparing the performance of integral increment
// operations using std::atomics versus a local accumulator
// protected by a std::mutex.
//
// Obviously not really a fair fight. Inspired by the CppCon 2017
// talk by Fedor Pikus "C++ Atomics" and actually meant to 
// illustrate the fact that algorithmic efficiency almost always
// trumps efficiency gains from reducing sharing / contention.

#include <benchmark/benchmark.h>

#include <mutex>
#include <chrono>
#include <vector>
#include <atomic>
#include <thread>
#include <iostream>
#include <condition_variable>

constexpr static std::size_t const TOTAL_WORK = 1 << 20;

static void atomic_increment_worker(
    std::atomic<bool>&        release_flag, 
    std::atomic<std::size_t>& count,
    std::size_t const         work_per_thread)
{
    // wait until all threads have started (busy wait)
    while (!release_flag.load())
    {
        std::this_thread::yield();
    }

    for (auto i = 0ul; i < work_per_thread; ++i)
    {
        count.fetch_add(1);
    }
}

static void BM_AtomicIncrement(benchmark::State& state)
{
    auto const n_threads       = static_cast<std::size_t>(state.range(0));
    auto const work_per_thread = TOTAL_WORK / n_threads;

    for (auto _ : state)
    {
        std::atomic<std::size_t> count{0};
        
        std::atomic<bool> release_flag{false};

        // launch all the threads
        std::vector<std::thread> threads{};
        for (auto i = 0ul; i < n_threads; ++i)
        {
            threads.emplace_back(
                atomic_increment_worker, 
                std::ref(release_flag),
                std::ref(count), 
                work_per_thread);
        }

        auto const start = std::chrono::high_resolution_clock::now();

        // release the threads
        release_flag.store(true);

        for (auto& t : threads)
        {
            t.join();
        }

        auto const end = std::chrono::high_resolution_clock::now();
        
        auto const elapsed = std::chrono::duration_cast<
            std::chrono::duration<double>>(end - start);

        state.SetIterationTime(elapsed.count());
    }
}

static void locked_increment_worker(
    std::atomic<bool>&       release_flag,
    std::mutex&              count_lock, 
    std::size_t&             count,
    std::size_t const        work_per_thread)
{
    // wait until all threads have started (busy wait)
    while (!release_flag.load())
    {
        std::this_thread::yield();
    }

    std::size_t local_count{0};
    for (auto i = 0ul; i < work_per_thread; ++i)
    {
        local_count++;
    }

    {
        std::scoped_lock guard{count_lock};
        count += local_count;
    }
}

static void BM_LockedIncrement(benchmark::State& state)
{
    auto const n_threads       = static_cast<std::size_t>(state.range(0));
    auto const work_per_thread = TOTAL_WORK / n_threads;

    for (auto _ : state)
    {
        std::size_t count{0};
        std::mutex count_lock{};

        std::atomic<bool> release_flag{false};

        // launch all the threads
        std::vector<std::thread> threads{};
        for (auto i = 0ul; i < n_threads; ++i)
        {
            threads.emplace_back(
                locked_increment_worker, 
                std::ref(release_flag),
                std::ref(count_lock), 
                std::ref(count), 
                work_per_thread);
        }

        auto const start = std::chrono::high_resolution_clock::now();

        // release the threads
        release_flag.store(true);

        for (auto& t : threads)
        {
            t.join();
        }

        auto const end = std::chrono::high_resolution_clock::now();
        
        auto const elapsed = std::chrono::duration_cast<
            std::chrono::duration<double>>(end - start);

        state.SetIterationTime(elapsed.count());
    }
}

// run the benchmark, varying the number of threads used on the 
// range [2, 32], mutliplying the number of threads by 2 in each iteration
BENCHMARK(BM_AtomicIncrement)->RangeMultiplier(2)->Range(2, 32)->UseManualTime();
BENCHMARK(BM_LockedIncrement)->RangeMultiplier(2)->Range(2, 32)->UseManualTime();

BENCHMARK_MAIN();