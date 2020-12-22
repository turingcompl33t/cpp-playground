// it_works.cpp

// C4459: declaration hides global
#pragma warning(disable : 4459)

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <random>
#include <range/v3/algorithm.hpp>

TEST_CASE("it works") 
{
    std::vector<int> v1{4, 3, 2, 1};
    std::vector<int> v2{4, 3, 2, 1};

    std::sort(v1.begin(), v1.end());
    ranges::sort(v2);

    auto const match = std::equal(v1.cbegin(), v1.cend(), v2.cbegin());
    REQUIRE(match);
}

TEST_CASE("it works with some additional input")
{
    std::mt19937_64 gen{};

    std::vector<int> v1(100);
    std::generate(v1.begin(), v1.end(), [n = 0]() mutable { return n++; });
    std::shuffle(v1.begin(), v1.end(), gen);

    std::vector<int> v2{v1.cbegin(), v1.cend()};

    REQUIRE(v1.size() == 100);
    REQUIRE(v2.size() == 100);

    std::sort(v1.begin(), v1.end());
    ranges::sort(v2);

    auto const match = std::equal(v1.cbegin(), v1.cend(), v2.cbegin());
    REQUIRE(match);
}