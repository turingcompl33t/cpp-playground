// bistset.cpp
// Demo of basic properties and usage of std::bitset.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 bitset.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <bitset>
#include <limits>

enum Color
{
    red,
    yellow, 
    green,
    blue,
    n_colors
};

TEST_CASE("std::bitset can be used to maintain a set of flags")
{
    auto c = std::bitset<Color::n_colors>{};

    c.set(Color::red);
    c.set(Color::blue);

    REQUIRE(c.count() == 2);
    
    REQUIRE(c.test(Color::red));
    REQUIRE(c.test(Color::blue));
    REQUIRE_FALSE(c.test(Color::green));
}

TEST_CASE("std::bitset can be used to convert integral values to their binary representation")
{
    SECTION("unsigned short")
    {
        auto c = std::bitset<std::numeric_limits<unsigned short>::digits>(267);
        REQUIRE(c.to_string() == "0000000100001011");
    }

    SECTION("unsigned long")
    {
        auto c = std::bitset<std::numeric_limits<unsigned long>::digits>(267);
        REQUIRE(c.to_string() == "00000000000000000000000100001011");
    }
}

TEST_CASE("std:bitset can be used to convert binary representations to integral values")
{
    SECTION("unsigned short")
    {
        auto c = std::bitset<std::numeric_limits<unsigned short>::digits>("0000000100001011");
        REQUIRE(c.to_ulong() == 267);
    }

    SECTION("unsigned long")
    {
        auto c = std::bitset<std::numeric_limits<unsigned long>::digits>(
            "00000000000000000000000100001011");
        REQUIRE(c.to_ulong() == 267);
    }
}