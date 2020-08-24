// bench.cpp

#include "benchmark/benchmark.h"

#include <chrono>
#include <vector>
#include <thread>

#include "spsc_queue.hpp"

// single-threaded ping-pong benchmark
static void BM_spsc_queue_ping_pong_st(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const work_count = static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        spsc_queue<std::size_t> queue{};

        auto const start = hr_clock::now();

        for (auto i = 0ul; i < work_count; ++i)
        {
            queue.push(i);
            queue.pop();
        }

        auto const stop = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<
            std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(static_cast<int64_t>(work_count));
    }
}

static void producer(
    spsc_queue<std::size_t>& queue, 
    std::atomic<bool>&       release_flag,
    std::size_t const        work_count)
{
    while (!release_flag.load(std::memory_order_acquire))
    {
        ;
    }

    for (auto i = 0ul; i < work_count; ++i)
    {
        queue.push(i);
    }
}

static void consumer(
    spsc_queue<std::size_t>& queue, 
    std::atomic<bool>&       release_flag,
    std::size_t const        work_count)
{
    while (!release_flag.load(std::memory_order_acquire))
    {
        ;
    }

    std::size_t pop_count{0};
    while (pop_count < work_count)
    {
        auto popped = queue.pop();
        if (popped)
        {
            ++pop_count;
        }
    }
}

// multithreaded ping-pong benchmark
static void BM_spsc_queue_ping_pong_mt(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const work_count = static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        spsc_queue<std::size_t> queue{};

        std::atomic<bool> release_flag{false};
        auto producer_thread = std::thread{
            producer, std::ref(queue), std::ref(release_flag), work_count};
        auto consumer_thread = std::thread{
            consumer, std::ref(queue), std::ref(release_flag), work_count};

        auto const start = hr_clock::now();

        // release the threads
        release_flag.store(true, std::memory_order_release);

        // wait for them to complete
        producer_thread.join();
        consumer_thread.join();

        auto const stop = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<
            std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(static_cast<int64_t>(work_count));
    }
}

BENCHMARK(BM_spsc_queue_ping_pong_st)->RangeMultiplier(2)->Range(1 << 16, 1 << 22)->UseManualTime();
BENCHMARK(BM_spsc_queue_ping_pong_mt)->RangeMultiplier(2)->Range(1 << 16, 1 << 22)->UseManualTime();

BENCHMARK_MAIN();