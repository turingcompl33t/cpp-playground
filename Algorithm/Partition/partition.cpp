// partition.cpp
//
// Demo of std::partition()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 partition.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

TEST_CASE("std::partition()")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 0);

    auto is_even = [](int i){ return i % 2 == 0; };

    // predicate evaluates TRUE if the element is even;
    // std::partition() operates such that elements for which
    // the predicate evaluates to TRUE are ordered before those
    // for which it evaluates to FALSE
    // return value is iterator to first element of second group

    auto first_odd = std::partition(c.begin(), c.end(), is_even);

    // all elements before parition point are even
    REQUIRE(std::all_of(c.begin(), first_odd, is_even));

    // all elements after partition point are not even (odd)
    REQUIRE(std::none_of(first_odd, c.end(), is_even));

    // forgone conclusion (lol)
    REQUIRE(std::is_partitioned(c.begin(), c.end(), is_even));
}