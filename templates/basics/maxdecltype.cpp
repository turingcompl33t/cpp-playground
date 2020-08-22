// maxdecltype.cpp
// Simple function template with decltype return type deduction.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 maxdecltype.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <type_traits>

template <typename T>
auto max(T a, T b) -> decltype(true?a:b)
{
    return b < a ? a : b;
}

template <typename T>
auto max_decay(T a, T b) -> std::decay_t<decltype(true?a:b)>
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

    SECTION("strings without decay (std::string)")
    {
        auto a = std::string{"hello"};
        auto b = std::string{"world"};

        // initialization of type auto always decays
        // thus: r is of type std::string even though the 
        // return type for ::max() deduced here is std::string&
        auto r = ::max(a, b);

        // this will fail because the return type is not decayed
        // and thus we return a std::string by value which results
        // in the return of a local variable
        CHECK(r == b);

        REQUIRE(std::is_same_v<decltype(r), std::string>);
    }

    SECTION("strings with decay (std::string)")
    {
        auto a = std::string{"hello"};
        auto b = std::string{"world"};

        auto r = ::max_decay(a, b);
        
        REQUIRE(r == b);
        REQUIRE(std::is_same_v<decltype(r), std::string>);
    }
}