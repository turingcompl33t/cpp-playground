// negate.cpp
//
// Fun with higher order functions.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 negate.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

template <typename Function>
auto negate(Function fn)
{
    return [fn](auto... args)
    {
        return !fn(args...);
    };
}

TEST_CASE("negate function template returns a function object \
    that computes the negation of passed function object")
{
    SECTION("is_even()")
    {
        auto is_even = [](int i){ return i%2 == 0; };

        auto is_odd = ::negate(is_even);

        REQUIRE(is_odd(3));
        REQUIRE_FALSE(is_odd(2));
    }

    SECTION("is_empty()")
    {
        auto is_empty = [](auto const& c){ return c.empty(); };
        auto is_nonempty = ::negate(is_empty);

        auto c1 = std::vector<int>{1};
        auto c2 = std::vector<int>{};

        REQUIRE(is_nonempty(c1));
        REQUIRE_FALSE(is_nonempty(c2));
    }
}