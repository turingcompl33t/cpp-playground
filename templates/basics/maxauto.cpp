// maxauto.cpp
// Simple function template with return type deduction.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 maxauto.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <type_traits>

template <typename T>
auto max(T a, T b)
{
    return b < a ? a : b;
}

TEST_CASE("max correctly computes maximum values and deduces return type for")
{
    SECTION("integers (long)")
    {
        auto a = 1l;
        auto b = 2l;

        auto r = ::max(a, b);
        REQUIRE(r == b);
        REQUIRE(std::is_same_v<decltype(r), long>);
    }

    SECTION("floating points (float)")
    {
        auto a = 1.0f;
        auto b = 2.0f;

        auto r = ::max(a, b);
        REQUIRE(r == b);
        REQUIRE(std::is_same_v<decltype(r), float>);
    }

    SECTION("strings (std::string)")
    {
        auto a = std::string{"hello"};
        auto b = std::string{"world"};

        auto r = ::max(a, b);
        REQUIRE(r == b);
        REQUIRE(std::is_same_v<decltype(r), std::string>);
    }
}