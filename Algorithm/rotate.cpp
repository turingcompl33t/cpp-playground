// rotate.cpp
//
// Demo of std::rotate()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 rotate.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

TEST_CASE("std::rotate()")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 0);  // 0 - 9

    REQUIRE(c.front() == 0);
    REQUIRE(c.back() == 9);

    std::rotate(c.begin(), c.begin() + 4, c.end());

    REQUIRE(c.front() == 4);
    REQUIRE(c.back() == 3);
}