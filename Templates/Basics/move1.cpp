// move1.cpp
// Demo of basic move semantics without template use
// - for contrast with move2 and move3
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 move1.cpp

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

overload f(X& x)
{
    return g(x);
}

overload f(X const& x)
{
    return g(x);
}

overload f(X&& x)
{
    // note that we need explicit std::move here to 
    // propogate the moveable-ness of the parameter
    return g(std::move(x));
}

TEST_CASE("The expected function is invoked via manual overloading")
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

    SECTION("with movable object")
    {
        auto val = X{};
        REQUIRE(f(std::move(val)) == overload::rvalue);
    }
}