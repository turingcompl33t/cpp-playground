// test.cpp

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <future>

#include "stack.hpp"

constexpr static auto const N_PRODUCERS = 2ul;
constexpr static auto const N_CONSUMERS = 2ul;

constexpr static auto const WORK_PER_THREAD = 10'000ul;

TEST_CASE("lock-free stack with quiescent state based reclamation supports construction")
{
    stack<int> s{};
    REQUIRE(s.is_empty_unsafe());
}

std::size_t producer(stack<std::size_t>& s)
{
    std::size_t pushed{0};
    for (auto i = 0ul; i < WORK_PER_THREAD; ++i)
    {
        s.push(i);
        ++pushed;
    }

    return pushed;
}

std::size_t consumer(stack<std::size_t>& s)
{
    std::size_t popped{0};
    for (auto i = 0ul; i < WORK_PER_THREAD; ++i)
    {
        auto result = s.pop();
        ++popped;
    }

    return popped;
}

TEST_CASE("lock-free stack with quiescent state based reclamation supports concurrent operations")
{
    using results_t = std::vector<std::future<std::size_t>>;

    stack<std::size_t> s{};

    REQUIRE(s.is_empty_unsafe());

    results_t producer_results{};
    for (auto i = 0ul; i < N_PRODUCERS; ++i)
    {
        producer_results.emplace_back(
            std::async(std::launch::async, producer, std::ref(s)));
    }

    results_t consumer_results{};
    for (auto i = 0ul; i < N_CONSUMERS; ++i)
    {
        consumer_results.emplace_back(
            std::async(std::launch::async, consumer, std::ref(s)));
    }

    for (auto& fut : producer_results)
    {
        REQUIRE(fut.get() == WORK_PER_THREAD);
    }

    for (auto& fut : consumer_results)
    {
        REQUIRE(fut.get() == WORK_PER_THREAD);
    }

    // drain the stack contents
    std::shared_ptr<std::size_t> popped{};
    do
    {
        popped = s.pop();
    } while (popped);

    REQUIRE(s.is_empty_unsafe());
}