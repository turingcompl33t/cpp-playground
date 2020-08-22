// reverse.cpp
//
// Demo of std::reverse()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 reverse.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <algorithm>

TEST_CASE("std::reverse() can be used to reverse a string in place")
{
    auto s = std::string{"hello world"};
    std::reverse(std::begin(s), std::end(s));

    REQUIRE(s == "dlrow olleh");
}