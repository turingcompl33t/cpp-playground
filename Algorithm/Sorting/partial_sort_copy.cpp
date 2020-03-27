// partial_sort_copy.cpp
//
// Demo of std:partial_sort_copy()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 partial_sort_copy.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <random>
#include <numeric>
#include <algorithm>

TEST_CASE("std::partial_sort_copy() performs partial sort with copy to new container")
{
    auto src = std::vector<int>(10);
    auto dst = std::vector<int>(4);

    std::iota(std::begin(src), std::end(src), 0); // 0 - 9

    auto gen = std::mt19937{std::random_device{}()};
    std::shuffle(std::begin(src), std::end(src), gen);

    auto it = std::partial_sort_copy(
        std::begin(src), std::end(src),
        std::begin(dst), std::end(dst));

    REQUIRE(std::is_sorted(std::begin(dst), std::end(dst)));

    // iterator points to end of dst because it is the smaller container
    REQUIRE(it == std::end(dst));
}