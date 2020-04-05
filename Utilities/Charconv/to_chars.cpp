// to_chars.cpp
//
// Demo of <charconv>'s to_chars()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 to_chars.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <charconv>
#include <string_view>

TEST_CASE("std::to_chars() basic usage")
{
    // space for conversion output
    auto str = std::array<char, 16>{};

    // return value is std::to_chars_result
    auto [p, ec] = std::to_chars(str.data(), str.data() + str.size(), 42);

    REQUIRE(ec == std::errc{});  // no error
    REQUIRE(std::string_view(str.data(), p - str.data()) == "42");
}