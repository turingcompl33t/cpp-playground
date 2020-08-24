// test.cpp

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <vector>
#include <thread>

#include "spsc_queue.hpp"

constexpr static auto const N_WORKER_PAIRS  = 1ul;
constexpr static auto const WORK_PER_THREAD = 100ul;

TEST_CASE("spsc queue supports construction")
{
    spsc_queue<std::size_t> queue{};
    REQUIRE(queue.is_empty_unsafe());
}

TEST_CASE("spsc queue supports single-threaded operations")
{
    spsc_queue<std::size_t> queue{};

    REQUIRE(queue.is_empty_unsafe());

    for (auto i = 0ul; i < WORK_PER_THREAD; ++i)
    {
        queue.push(i);
    }

    for (auto i = 0ul; i < WORK_PER_THREAD; ++i)
    {
        auto popped = queue.pop();
        REQUIRE(*popped == i);
    }

    REQUIRE(queue.is_empty_unsafe());
}

void producer(spsc_queue<std::size_t>& queue)
{
    for (auto i = 0ul; i < WORK_PER_THREAD; ++i)
    {
        queue.push(i);
    }
}

void consumer(spsc_queue<std::size_t>& queue)
{
    std::size_t pop_count{0};
    while (pop_count < WORK_PER_THREAD)
    {
        // pop() may return empty shared_ptr in the event queue is empty
        auto popped = queue.pop();
        if (popped)
        {
            ++pop_count;
        }
    }
}

TEST_CASE("spsc queue supports concurrent operations")
{
    spsc_queue<std::size_t> queue{};

    REQUIRE(queue.is_empty_unsafe());

    std::vector<std::thread> threads{};
    for (auto i = 0ul; i < N_WORKER_PAIRS; ++i)
    {
        threads.emplace_back(producer, std::ref(queue));
        threads.emplace_back(consumer, std::ref(queue));
    }

    for (auto& t: threads)
    {
        t.join();
    }

    REQUIRE(queue.is_empty_unsafe());
}