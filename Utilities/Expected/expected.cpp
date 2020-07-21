// expected.cpp
//
// Build
//  gcc -Wall -Werror -pedantic -std=c++2a -I${CPP_WORKSPACE}/_Deps/catch2/include expected.cpp -o expected.out

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("it works")
{
    REQUIRE(true);
}