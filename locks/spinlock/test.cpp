// test.cpp
// Tests for basic correctness of spinlock implementations.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <thread>

#include "guard.hpp"
#include "naive_spinlock.hpp"
#include "tatas_spinlock.hpp"
#include "yielding_spinlock.hpp"

constexpr static auto const N_THREADS      = 16ul;
constexpr static auto const OPS_PER_THREAD = 1'000ul;

template <typename LockType>
static void worker(LockType& lock, std::size_t& count)
{
    for (auto i = 0ul; i < OPS_PER_THREAD; ++i)
    {
        guard<LockType> g{lock};
        ++count;
    }
}

TEST_CASE("naive_spinlock protects shared data")
{
    std::size_t shared_count{0};

    naive_spinlock lock{};

    std::vector<std::thread> threads{};
    for (auto i = 0ul; i < N_THREADS; ++i)
    {
        threads.emplace_back(
            worker<naive_spinlock>, 
            std::ref(lock), 
            std::ref(shared_count));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    REQUIRE(shared_count == N_THREADS*OPS_PER_THREAD);
}

TEST_CASE("tatas_spinlock protects shared data")
{
    std::size_t shared_count{0};

    tatas_spinlock lock{};

    std::vector<std::thread> threads{};
    for (auto i = 0ul; i < N_THREADS; ++i)
    {
        threads.emplace_back(
            worker<tatas_spinlock>, 
            std::ref(lock), 
            std::ref(shared_count));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    REQUIRE(shared_count == N_THREADS*OPS_PER_THREAD);
}

TEST_CASE("yielding_spinlock protects shared data")
{
    std::size_t shared_count{0};

    yielding_spinlock lock{};

    std::vector<std::thread> threads{};
    for (auto i = 0ul; i < N_THREADS; ++i)
    {
        threads.emplace_back(
            worker<yielding_spinlock>, 
            std::ref(lock), 
            std::ref(shared_count));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    REQUIRE(shared_count == N_THREADS*OPS_PER_THREAD);
}