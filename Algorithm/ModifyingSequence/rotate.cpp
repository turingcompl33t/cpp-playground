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

TEST_CASE("std::rotate() can rotate an entire range")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 1);  // 1 - 10

    REQUIRE(c.front() == 1);
    REQUIRE(c.back() == 10);

    std::rotate(c.begin(), c.begin() + 3, c.end());

    REQUIRE(c.front() == 4);
    REQUIRE(c.back() == 3);
}

TEST_CASE("std::rotate() can rotate a subrange within a larger range")
{
    auto c = std::vector<int>(10);
    std::iota(std::begin(c), std::end(c), 1); // 1 - 10

    REQUIRE(*(std::begin(c)+1) == 2);
    REQUIRE(*(std::begin(c)+4) == 5);

    std::rotate(std::begin(c) + 1, std::begin(c) + 4, std::begin(c) + 5);

    REQUIRE(*(std::begin(c)+1) == 5);
    REQUIRE(*(std::begin(c)+4) == 4);
}

TEST_CASE("std::rotate() can be combined with std::stable_parition()\
    to perform some relatively complex modifying sequence operations")
{
    auto c = std::vector<int>(10);
    std::iota(std::begin(c), std::end(c), 1); // 1 - 10

    auto even = [](int i){ return i % 2 == 0; };

    // move all even numbers to the front of the container
    auto p = std::stable_partition(std::begin(c), std::end(c), even);

    // rotate the entire subrange
    std::rotate(std::begin(c), p, p + 1);

    auto it = std::begin(c);
    REQUIRE(*it++ == 1);
    REQUIRE(*it++ == 2);
}