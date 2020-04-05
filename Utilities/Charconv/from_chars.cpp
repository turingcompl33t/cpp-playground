// from_chars.cpp
//
// Demo of <charconv>'s from_chars()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 from_chars.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <charconv>

TEST_CASE("std::from_chars() basic usage")
{
    auto str = std::array<char, 16>{"42"};
    auto res = int{};

    auto [p, ec] = std::from_chars(str.data(), str.data() + str.size(), res);

    REQUIRE(ec == std::errc{});
    REQUIRE(res == 42);
}