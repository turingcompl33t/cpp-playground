// addvalue.cpp
// Demo of basic nontype template arguments with function templates.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 addvalue.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>

template <auto Val, typename T = decltype(Val)>
T addvalue(T x)
{
    return x + Val;
} 

TEST_CASE("addvalue() function works for")
{
    SECTION("primitive types (int)")
    {
        auto i = int{5};

        auto r1 = ::addvalue<5>(i);
        REQUIRE(r1 == 10);
        REQUIRE(std::is_same_v<decltype(r1), int>);

        auto r2 = ::addvalue<15>(i);
        REQUIRE(r2 == 20);
        REQUIRE(std::is_same_v<decltype(r2), int>);
    }
}

TEST_CASE("addvalue() may be used in STL algorithms")
{
    SECTION("std::transform()")
    {
        std::vector<int> v{1, 2, 3, 4, 5};

        // add 5 to each member of v
        std::transform(
            std::begin(v), 
            std::end(v), 
            std::begin(v), 
            ::addvalue<5>
            );

        REQUIRE(v[0] == 6);
        REQUIRE(v[1] == 7);
        REQUIRE(v[2] == 8);
        REQUIRE(v[3] == 9);
        REQUIRE(v[4] == 10);
    }
}

