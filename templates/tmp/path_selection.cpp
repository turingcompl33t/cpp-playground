// path_selection.cpp
// Execution path selection with partial specialization.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I %CPP_WORKSPACE%\_Deps\Catch2 path_selection.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>

constexpr bool is_even(int n)
{
    return n % 2 == 0;
}

template <int Size, bool = is_even(Size)>
struct size_helper;

template <int Size>
struct size_helper<Size, true>
{
    bool value = true;
};

template <int Size>
struct size_helper<Size, false>
{
    bool value = false;
};

template <typename T, std::size_t Size>
bool foo(std::array<T, Size> const&)
{
    size_helper<Size> helper{};
    return helper.value;
}

TEST_CASE("execution path is selected based on array size")
{
    SECTION("with array containing an even number of elements")
    {
        std::array<int, 2> a{1, 2};
        REQUIRE(foo(a));
    }

    SECTION("with array containing an odd number of elements")
    {
        std::array<int, 3> a{1, 2, 3};
        REQUIRE_FALSE(foo(a));
    }
}