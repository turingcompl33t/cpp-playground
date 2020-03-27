// for_each.cpp
//
// Demo of std::for_each(), std::for_each_n
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 for_each.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <list>
#include <algorithm>

TEST_CASE("std::for_each() applies a function to each element in a range")
{
    // NOTE: horrible way to compute a sum;
    // std::accumulate() will likely be crying itself to sleep tonight 

    auto c = std::list<int>{1, 2, 3, 4};

    auto sum = 0ul;

    std::for_each(std::begin(c), std::end(c),
        [&sum](int i)
        {
            sum += i;
        });
    
    REQUIRE(sum == 10);
}

TEST_CASE("std::for_each_n() applies a function to the first n elements in the specified range")
{
    auto c = std::list<int>{1, 2, 3, 4};

    auto sum = 0ul;

    std::for_each_n(std::begin(c), 3,
        [&sum](int i)
        {
            sum += i;
        });

    REQUIRE(sum == 6);
}