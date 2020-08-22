// max1.cpp
// Simple function template.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 max1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>

template <typename T>
T max(T a, T b)
{
    return b < a ? a : b;
}

TEST_CASE("max correctly computes maximum of two values for")
{
    SECTION("integers (long)")
    {
        auto a = 1l;
        auto b = 2l;

        auto r = ::max(a, b);
        REQUIRE(r == 2l);
    }

    SECTION("floating point (float)")
    {
        auto a = 1.0f;
        auto b = 2.0f;

        auto r = ::max(a, b);
        REQUIRE(r == 2.0f);
    }

    SECTION("strings (std::string)")
    {
        auto a = std::string{"hello"};
        auto b = std::string{"world"};

        auto r = ::max(a, b);
        REQUIRE(r == b);
    }
}