// yield_perf.cpp
//
// Build
//  cl /EHsc /nologo /std:c++latest /await /W4 yield_perf.cpp

#include <chrono>
#include <iostream>
#include <experimental/generator>

std::chrono::milliseconds 
raw_test(long long const iterations)
{
    auto const start = std::chrono::high_resolution_clock::now();

    auto accum1 = long long{};

    for (auto i = 0ll; i < iterations; ++i)
    {
        accum1 += i;
    }

    auto const stop = std::chrono::high_resolution_clock::now();
    auto const duration = stop - start; 

    return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}

std::experimental::generator<long long> 
generator(long long const iterations)
{
    for (auto i = 0ll; i < iterations; ++i)
    {
        co_yield i;
    }
}

std::chrono::milliseconds 
coro_test(long long const iterations)
{
    auto const start = std::chrono::high_resolution_clock::now();

    auto accum = long long{};
    for (auto i : generator(iterations))
    {
        accum += i;
    }

    auto const stop = std::chrono::high_resolution_clock::now();
    auto const duration = stop - start;

    return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}

int main()
{
    auto const iterations = 100000000ll;

    auto const raw_ms = raw_test(iterations);
    auto const coro_ms = coro_test(iterations);

    auto const raw_count = raw_ms.count();
    auto const coro_count = coro_ms.count();

    auto const diff = coro_count / raw_count;

    std::cout << "Raw time:  " << raw_count << " ms\n";
    std::cout << "Coro time: " << coro_count << " ms\n";
    std::cout << "Performance diff: " << diff << "X\n";

    return 0;
}