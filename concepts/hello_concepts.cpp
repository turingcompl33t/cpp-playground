// hello_concepts.cpp
// Test of concept support in MSVC.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++latest /I %CPP_WORKSPACE%\_Deps\Catch2 hello_concepts.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iostream>
#include <type_traits>

template <typename T>
concept floating_point = std::is_floating_point_v<T>;

template <typename T>
T original_syntax(T a, T b) requires floating_point<T>
{
    return a + b;
}

template <floating_point T>
T improved_syntax(T a, T b)
{
    return a + b;
}

// terse syntax currently unsupported
// T terse_syntax(floating_point auto a, floating_point auto b)
// {
//     return a + b;
// }

TEST_CASE("concepts with original syntax")
{
    auto r = original_syntax(1.2, 3.4);
    REQUIRE(r == 4.6);
}

TEST_CASE("concepts with improved syntax")
{
    auto r = improved_syntax(1.2, 3.4);
    REQUIRE(r == 4.6);
}