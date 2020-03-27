// partial_sort.cpp
//
// Demo of std:partial_sort()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 partial_sort.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <random>
#include <numeric>
#include <algorithm>

TEST_CASE("std::partial_sort() ")
{
    auto c = std::vector<int>(10);
    std::iota(std::begin(c), std::end(c), 0);  // 0 - 9

     auto gen = std::mt19937{std::random_device{}()};
     std::shuffle(std::begin(c), std::end(c), gen);

     std::partial_sort(std::begin(c), std::begin(c) + 4, std::end(c));

     auto r = std::all_of(std::begin(c), std::begin(c) + 4, 
        [&c](int i)
        {
            return std::all_of(std::begin(c) + 4, std::end(c), [=](int j){ return i < j; });
        });

    REQUIRE(r);
}