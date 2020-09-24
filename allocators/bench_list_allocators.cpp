// bench_list_allocators.cpp
// Comparing the performance of std::list when used with different memory allocators.
//
// Observations:
// Failing to observe any real performance difference between the baseline
// that defaults to use of global new / delete and the pool allocators.

#include <benchmark/benchmark.h>

#include <list>
#include <chrono>
#include <memory_resource>

constexpr static std::size_t const N_OPS = 1 << 12;

constexpr static auto const MIN_CONTAINER_SIZE = 1 << 2;
constexpr static auto const MAX_CONTAINER_SIZE = 1 << 12;

void BM_list_baseline(benchmark::State& state)
{
    using item_t   = std::size_t;
    using hr_clock = std::chrono::high_resolution_clock;

    auto const n_items = static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        // fill the list with the prescribed number of items
        std::list<item_t> list{};
        for (auto i = 0ul; i < n_items; ++i)
        {
            list.push_back(i);
        }

        auto const start = hr_clock::now();

        // remove and re-insert items from list
        for (auto i = 0ul; i < N_OPS; ++i)
        {
            auto const p = list.front();
            list.pop_front();
            list.push_back(p);
        }

        auto const stop = hr_clock::now();

        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(N_OPS);
    }
}

void BM_list_new_delete(benchmark::State& state)
{
    using item_t   = std::size_t;
    using hr_clock = std::chrono::high_resolution_clock;

    auto const n_items = static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        // construct a list that utilizes a polymorphic allocator 
        // backed by the default std::pmr::new_delete_resource
        std::pmr::list<item_t> list{
            std::pmr::polymorphic_allocator<std::byte>{std::pmr::new_delete_resource()}};
        for (auto i = 0ul; i < n_items; ++i)
        {
            list.push_back(i);
        }

        auto const start = hr_clock::now();

        // remove and re-insert items from list
        for (auto i = 0ul; i < N_OPS; ++i)
        {
            auto const p = list.front();
            list.pop_front();
            list.push_back(p);
        }

        auto const stop = hr_clock::now();

        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(N_OPS);
    }
}

void BM_list_synchronized_pool(benchmark::State& state)
{
    using item_t   = std::size_t;
    using hr_clock = std::chrono::high_resolution_clock;

    auto const n_items = static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        // construct the memory resource
        std::pmr::synchronized_pool_resource mr{std::pmr::pool_options{0, 64}};

        // construct a list that utilizes a polymorphic allocator 
        // backed by the synchronized pool resource 
        std::pmr::list<item_t> list{
            std::pmr::polymorphic_allocator<std::byte>{std::addressof(mr)}};
        for (auto i = 0ul; i < n_items; ++i)
        {
            list.push_back(i);
        }

        auto const start = hr_clock::now();

        // remove and re-insert items from list
        for (auto i = 0ul; i < N_OPS; ++i)
        {
            auto const p = list.front();
            list.pop_front();
            list.push_back(p);
        }

        auto const stop = hr_clock::now();

        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(N_OPS);
    }
}

void BM_list_unsynchronized_pool(benchmark::State& state)
{
    using item_t   = std::size_t;
    using hr_clock = std::chrono::high_resolution_clock;

    auto const n_items = static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        // construct the memory resource
        std::pmr::unsynchronized_pool_resource mr{std::pmr::pool_options{0, 64}};

        // construct a list that utilizes a polymorphic allocator 
        // backed by the unsynchronized pool resource 
        std::pmr::list<item_t> list{
            std::pmr::polymorphic_allocator<std::byte>{std::addressof(mr)}};
        for (auto i = 0ul; i < n_items; ++i)
        {
            list.push_back(i);
        }

        auto const start = hr_clock::now();

        // remove and re-insert items from list
        for (auto i = 0ul; i < N_OPS; ++i)
        {
            auto const p = list.front();
            list.pop_front();
            list.push_back(p);
        }

        auto const stop = hr_clock::now();

        auto const elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(elapsed.count());
        state.SetItemsProcessed(N_OPS);
    }
}

BENCHMARK(BM_list_baseline)->RangeMultiplier(2)->Range(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE)->UseManualTime();
BENCHMARK(BM_list_new_delete)->RangeMultiplier(2)->Range(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE)->UseManualTime();
BENCHMARK(BM_list_synchronized_pool)->RangeMultiplier(2)->Range(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE)->UseManualTime();
BENCHMARK(BM_list_unsynchronized_pool)->RangeMultiplier(2)->Range(MIN_CONTAINER_SIZE, MAX_CONTAINER_SIZE)->UseManualTime();

BENCHMARK_MAIN();