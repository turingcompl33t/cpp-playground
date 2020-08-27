// bench_lookup.cpp
// Benchmarking the lookup performance for various STL containers
// as the number of items stored in the container increases.

#include "benchmark/benchmark.h"

#include <random>
#include <chrono>
#include <cstdlib>

#include <map>
#include <vector>
#include <unordered_map>

// seed for random number generation
constexpr static std::uint_fast32_t const RNG_SEED = 1;

// minimum and maximum container sizes
constexpr static std::int64_t const MIN_N_ITEMS = 1 << 5;
constexpr static std::int64_t const MAX_N_ITEMS = 1 << 16;

// temporary buffer size
constexpr static std::size_t const BUFFER_SIZE = 64;

// simple RNG wrapper
struct rng
{
    std::mt19937                       generator;
    std::uniform_int_distribution<int> distribution;
    
    std::size_t const count;

public: 
    explicit rng(
        std::uint_fast32_t const seed_, 
        std::size_t const       count_) 
        : generator{seed_}
        , distribution{0}
        , count{count_}
    {}

    struct iterator
    {
        rng&        owner;
        std::size_t count;

        bool operator!=(iterator const& rhs) const
        {
            return rhs.count != count;
        }

        iterator& operator++()
        {
            --count;
            return *this;
        }

        int operator*()
        {
            return owner.distribution(owner.generator);
        }
    };

    iterator begin()
    {
        return iterator{*this, count};
    }

    iterator end()
    {
        return iterator{*this, 0};
    }
};

template <typename ContainerType>
void fill_container_and_lookups(
    ContainerType&    container, 
    std::size_t const n_items, 
    std::vector<int>& lookups, 
    std::size_t const n_lookups);

template <>
void fill_container_and_lookups(
    std::vector<int>& container, 
    std::size_t const n_items, 
    std::vector<int>& lookups, 
    std::size_t const n_lookups)
{
    auto const ratio = n_items / n_lookups;

    container.reserve(n_items);
    lookups.reserve(n_lookups);

    std::size_t n{0};
    for (auto const item : rng{RNG_SEED, n_items})
    {
        container.push_back(item);
        
        if (0 == (n++ % ratio))
        {
            lookups.push_back(item);
        }
    }
}

template <>
void fill_container_and_lookups(
    std::map<int, int>& container, 
    std::size_t const   n_items, 
    std::vector<int>&   lookups, 
    std::size_t const   n_lookups)
{
    auto const ratio = n_items / n_lookups;

    lookups.reserve(n_lookups);

    std::size_t n{0};
    for (auto const item : rng{RNG_SEED, n_items})
    {
        container.emplace(std::make_pair(item, item));

        if (0 == (n++ % ratio))
        {
            lookups.push_back(item);
        }
    }
}

template <>
void fill_container_and_lookups(
    std::unordered_map<int, int>& container, 
    std::size_t const             n_items, 
    std::vector<int>&             lookups, 
    std::size_t const             n_lookups)
{
    auto const ratio = n_items / n_lookups;

    lookups.reserve(n_lookups);

    std::size_t n{0};
    for (auto const item : rng{RNG_SEED, n_items})
    {
        container.emplace(std::make_pair(item, item));

        if (0 == (n++ % ratio))
        {
            lookups.push_back(item);
        }
    }
}

// linear search on a std::vector
static void BM_vector(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    // the number of items inserted into the container
    auto const n_items   = static_cast<std::size_t>(state.range(0));
    auto const n_lookups = (n_items >> 2);

    std::vector<int> container{};
    std::vector<int> lookups{};

    fill_container_and_lookups(container, n_items, lookups, n_lookups);

    auto const begin = std::begin(container);
    auto const end   = std::end(container);

    for (auto _ : state)
    {
        auto const start = hr_clock::now();

        for (auto const l : lookups)
        {
            benchmark::DoNotOptimize(std::find(begin, end, l));
        }

        auto const stop = hr_clock::now();
        auto const as_double = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(as_double.count());

        auto const as_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        auto const ns_per_lookup = static_cast<std::size_t>(as_ns.count()) / n_lookups;

        char message[BUFFER_SIZE];
        ::snprintf(message, sizeof(message), "%zu ns per lookup", ns_per_lookup);
        
        state.SetLabel(message);
    }
}

// lookup on std::map
static void BM_map(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    // the number of items inserted into the container
    auto const n_items   = static_cast<std::size_t>(state.range(0));
    auto const n_lookups = (n_items >> 2);

    std::map<int, int> container{};
    std::vector<int>   lookups{};

    fill_container_and_lookups(container, n_items, lookups, n_lookups);

    for (auto _ : state)
    {
        auto const start = hr_clock::now();

        for (auto const l : lookups)
        {
            benchmark::DoNotOptimize(container.find(l));
        }

        auto const stop = hr_clock::now();
        auto const as_double = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(as_double.count());

        auto const as_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        auto const ns_per_lookup = static_cast<std::size_t>(as_ns.count()) / n_lookups;

        char message[BUFFER_SIZE];
        ::snprintf(message, sizeof(message), "%zu ns per lookup", ns_per_lookup);
        
        state.SetLabel(message);
    }
}

// lookup on std::unordered_map
static void BM_unordered_map(benchmark::State& state)
{
    using hr_clock = std::chrono::high_resolution_clock;

    // the number of items inserted into the container
    auto const n_items   = static_cast<std::size_t>(state.range(0));
    auto const n_lookups = (n_items >> 2);

    std::unordered_map<int, int> container{};
    std::vector<int>             lookups{};
    
    fill_container_and_lookups(container, n_items, lookups, n_lookups);

    for (auto _ : state)
    {
        auto const start = hr_clock::now();

        for (auto const l : lookups)
        {
            benchmark::DoNotOptimize(container.find(l));
        }

        auto const stop = hr_clock::now();
        auto const as_double = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        state.SetIterationTime(as_double.count());

        auto const as_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        auto const ns_per_lookup = static_cast<std::size_t>(as_ns.count()) / n_lookups;

        char message[BUFFER_SIZE];
        ::snprintf(message, sizeof(message), "%zu ns per lookup", ns_per_lookup);
        
        state.SetLabel(message);
    }
}

BENCHMARK(BM_vector)->RangeMultiplier(2)->Range(MIN_N_ITEMS, MAX_N_ITEMS)->UseManualTime();
BENCHMARK(BM_map)->RangeMultiplier(2)->Range(MIN_N_ITEMS, MAX_N_ITEMS)->UseManualTime();
BENCHMARK(BM_unordered_map)->RangeMultiplier(2)->Range(MIN_N_ITEMS, MAX_N_ITEMS)->UseManualTime();

BENCHMARK_MAIN();