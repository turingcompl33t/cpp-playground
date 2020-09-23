// bench_list_deque.cpp
// Benchmarking the throughput of a inserts / deletes at one end of std::list vs std::deque.

#include "benchmark/benchmark.h"

#include <list>
#include <deque>
#include <chrono>
#include <memory>

constexpr static auto const N_OPS = 1'000'000;

constexpr static int64_t const MIN_CONTAINER_SIZE = 1;
constexpr static int64_t const MAX_CONTAINER_SIZE = 1 << 10;

template<class T> 
void pop_front(std::deque<T>& d)
{
	d.pop_front();
}

template<class T> 
void pop_front(std::list<T>& l)
{
	l.pop_front();
}

static void BM_list(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const container_size = static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        std::list<std::size_t> list{};
        for (auto i = 0ul; i < container_size; ++i)
        {
            list.push_back(i);
        }

        auto const start = hr_clock::now();

        for (auto i = 0ul; i < N_OPS; ++i)
        {
            auto w = list.front();
            pop_front(list);
            list.push_back(w);
        }

        auto const stop = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(N_OPS);
    }
}

static void BM_deque(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const container_size = static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        std::deque<std::size_t> deq{};
        for (auto i = 0ul; i < container_size; ++i)
        {
            deq.push_back(i);
        }

        auto const start = hr_clock::now();

        for (auto i = 0ul; i < N_OPS; ++i)
        {
            auto w = deq.front();
            pop_front(deq);
            deq.push_back(w);
        }

        auto const stop = hr_clock::now();
        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(N_OPS);
    }
}

BENCHMARK(BM_list)->RangeMultiplier(2)->Range(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE)->UseManualTime();
BENCHMARK(BM_deque)->RangeMultiplier(2)->Range(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE)->UseManualTime();

BENCHMARK_MAIN();