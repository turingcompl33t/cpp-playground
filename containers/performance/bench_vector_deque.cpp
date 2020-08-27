// bench_vector_deque.cpp
//
// Quick + dirty test of vector vs deque performance when
// removing the first element of the container.
//
// Takeaways: the performance of repeated pop_front() / push_back()
// operations on std::vector degrades rapidly as the size of the
// container increases; in contrast, the performance of std::deque
// under the same workload is incredibly consistent.

#include "benchmark/benchmark.h"

#include <vector>
#include <deque>
#include <chrono>
#include <memory>

constexpr static auto const N_OPS = 1'000'000;

constexpr static int64_t const MIN_CONTAINER_SIZE = 1;
constexpr static int64_t const MAX_CONTAINER_SIZE = 1 << 15;

template<class T> 
void pop_front(std::deque<T>& v)
{
	v.pop_front();
}

template<class T> 
void pop_front(std::vector<T>& v)
{
	v.erase(v.begin());
}

static void BM_vector(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    auto const container_size = static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        std::vector<std::size_t> vec{};
        vec.reserve(container_size);
        for (auto i = 0ul; i < container_size; ++i)
        {
            vec.push_back(i);
        }

        auto const start = hr_clock::now();

        for (auto i = 0ul; i < N_OPS; ++i)
        {
            auto w = vec.front();
            pop_front(vec);
            vec.push_back(w);
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

BENCHMARK(BM_vector)->RangeMultiplier(2)->Range(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE)->UseManualTime();
BENCHMARK(BM_deque)->RangeMultiplier(2)->Range(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE)->UseManualTime();

BENCHMARK_MAIN();