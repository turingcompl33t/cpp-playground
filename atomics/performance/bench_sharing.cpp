// bench_sharing.cpp
//
// A benchmark comparing the performance implications for atomics when:
//  - The atomic is shared explicitly
//  - The atomic is shared implicitly (false sharing)
//  - The atomic is unshared (multiple values)
//
// Typical run results:
//
// shared:       items_per_second=27.9436M/s
// false shared: items_per_second=28.3077M/s
// unshared:     items_per_second=270.42M/s

#include <benchmark/benchmark.h>

#include <array>
#include <chrono>
#include <atomic>
#include <thread>
#include <vector>

// assume the size of a cache line is 64 bytes
constexpr static std::size_t const CACHE_LINE_SIZE = 64;

// the total number of increments performed
constexpr static std::size_t const TOTAL_WORK = 1'000'000'000;

// just assume using four threads for this bench
constexpr static std::size_t const N_THREADS       = 4;
constexpr static std::size_t const WORK_PER_THREAD = TOTAL_WORK / N_THREADS;

struct SharedData
{
    std::atomic<std::size_t> count;

    SharedData() = default;
};

struct FalseSharedData
{
    std::array<std::atomic<std::size_t>, 4> counts;

    FalseSharedData() = default;
};

struct UnsharedData
{
    std::uint8_t pad0[CACHE_LINE_SIZE];
    
    std::atomic<std::size_t> count1;
    std::uint8_t pad1[CACHE_LINE_SIZE 
        - sizeof(std::atomic<std::size_t>)];

    std::atomic<std::size_t> count2;
    std::uint8_t pad2[CACHE_LINE_SIZE 
        - sizeof(std::atomic<std::size_t>)];

    std::atomic<std::size_t> count3;
    std::uint8_t pad3[CACHE_LINE_SIZE 
        - sizeof(std::atomic<std::size_t>)];

    std::atomic<std::size_t> count4;
    std::uint8_t pad4[CACHE_LINE_SIZE 
        - sizeof(std::atomic<std::size_t>)];

    UnsharedData() = default;
};

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
        shared_count.fetch_add(1, std::memory_order_relaxed);
    }
}

// benchmark atomic increments for explicitly shared variable
static void BM_shared(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    for (auto _ : state)
    {
        SharedData data{};

        std::atomic<bool> release_flag{false};
        
        std::vector<std::thread> threads{};
        for (auto i = 0ul; i < N_THREADS; ++i)
        {
            threads.emplace_back(
                shared_worker, 
                std::ref(release_flag), 
                std::ref(data.count), 
                WORK_PER_THREAD);
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
        state.SetItemsProcessed(TOTAL_WORK);
    }
}

static void false_shared_worker(
    std::atomic<bool>&        release_flag, 
    std::atomic<std::size_t>& count, 
    std::size_t const         work_per_thread)
{
    while (!release_flag.load())
    {
        std::this_thread::yield();
    }

    for (auto i = 0ul; i < work_per_thread; ++i)
    {
        count.fetch_add(1, std::memory_order_relaxed);
    }
}

static void BM_false_shared(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    for (auto _ : state)
    {
        FalseSharedData data{};

        std::atomic<bool> release_flag{false};
        
        std::vector<std::thread> threads{};
        threads.emplace_back(false_shared_worker, 
            std::ref(release_flag), std::ref(data.counts[0]), WORK_PER_THREAD);
        threads.emplace_back(false_shared_worker, 
            std::ref(release_flag), std::ref(data.counts[1]), WORK_PER_THREAD);
        threads.emplace_back(false_shared_worker, 
            std::ref(release_flag), std::ref(data.counts[2]), WORK_PER_THREAD);
        threads.emplace_back(false_shared_worker, 
            std::ref(release_flag), std::ref(data.counts[3]), WORK_PER_THREAD);

        auto const start = hr_clock::now();

        release_flag.store(true);

        for (auto& t : threads)
        {
            t.join();
        }

        auto const end = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(TOTAL_WORK);
    }
}

static void unshared_worker(
    std::atomic<bool>&        release_flag,
    std::atomic<std::size_t>& count, 
    std::size_t const         work_per_thread)
{
    while (!release_flag.load())
    {
        std::this_thread::yield();
    }

    for (auto i = 0ul; i < work_per_thread; ++i)
    {
        count.fetch_add(1, std::memory_order_relaxed);
    }
}

// benchmark atomic increments for unshared variables
static void BM_unshared(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    for (auto _ : state)
    {
        UnsharedData data{};

        std::atomic<bool> release_flag{false};

        std::vector<std::thread> threads{};
        threads.emplace_back(unshared_worker, 
            std::ref(release_flag), std::ref(data.count1), WORK_PER_THREAD);
        threads.emplace_back(unshared_worker, 
            std::ref(release_flag), std::ref(data.count2), WORK_PER_THREAD);
        threads.emplace_back(unshared_worker, 
            std::ref(release_flag), std::ref(data.count3), WORK_PER_THREAD);
        threads.emplace_back(unshared_worker, 
            std::ref(release_flag), std::ref(data.count4), WORK_PER_THREAD);

        auto const start = hr_clock::now();

        release_flag.store(true);

        for (auto& t : threads)
        {
            t.join();
        }

        auto const end = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(TOTAL_WORK);
    }
}


BENCHMARK(BM_shared)->UseManualTime();
BENCHMARK(BM_false_shared)->UseManualTime();
BENCHMARK(BM_unshared)->UseManualTime();

BENCHMARK_MAIN();