// thread_local.cpp
// Diagnosing issues with thread_local on gcc 10.

#include <future>
#include <vector>
#include <cassert>
#include <cstdlib>

constexpr static auto const N_THREADS = 2;
constexpr static auto const N_ITERS   = 5ul;

int worker()
{
    using namespace std::chrono_literals;

    static thread_local int local_counter{0};

    for (auto i = 0ul; i < N_ITERS; ++i)
    {
        local_counter++;
        std::this_thread::sleep_for(500ms);
    }

    return local_counter;
}

int main()
{
    std::vector<std::future<int>> results{};
    for (auto i = 0; i < N_THREADS; ++i)
    {
        results.emplace_back(std::async(std::launch::async, worker));
    }

    for (auto& fut : results)
    {
        assert(fut.get() == N_ITERS);
    }

    return EXIT_SUCCESS;
}