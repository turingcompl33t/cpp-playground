// move1.cpp
// Demo of basic move semantics with template and
// perfect forwarding.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 move2.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <utility>

class X {};

enum class overload
{
    lvalue,
    const_lvalue,
    rvalue
};

overload g(X&)
{
    return overload::lvalue;
}

overload g(X const&)
{
    return overload::const_lvalue;
}

overload g(X&&)
{
    return overload::rvalue;
}

template <typename T>
overload f(T&& x)
{
    return g(std::forward<T>(x));
}

TEST_CASE("The expected function is invoked via perfect forwarding")
{
    SECTION("with modifiable reference")
    {
        auto val = X{};
        REQUIRE(f(val) == overload::lvalue);
    }

    SECTION("with non-modifiable reference")
    {
        auto const val = X{};
        REQUIRE(f(val) == overload::const_lvalue);
    }

    SECTION("with temporary object")
    {
        REQUIRE(f(X{}) == overload::rvalue);
    }

    SECTION("with moveable object")
    {
        auto val = X{};
        REQUIRE(f(std::move(val)) == overload::rvalue);
    }
}
