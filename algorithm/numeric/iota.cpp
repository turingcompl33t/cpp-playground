// iota.cpp
// Usage of std::iota()

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <numeric>

TEST_CASE("std::iota() allows us to easily fill containers with data")
{
    auto c1 = std::vector<int>(10);
    auto c2 = std::vector<int>(10);

    std::iota(c1.begin(), c1.end(), 0);
    REQUIRE(c1.front() == 0);
    REQUIRE(c1.back() == 9);

    std::iota(c2.begin(), c2.end(), -5);
    REQUIRE(c2.front() == -5);
    REQUIRE(c2.back() == 4);
}