// accum0.cpp
// Using templates with traits types for customization points.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 accum0.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iterator>

#include <array>
#include <vector>

template <typename Iter>
auto accumulate(Iter beg, Iter end)
{
    using VT = typename std::iterator_traits<Iter>::value_type;

    auto total = VT{};
    while (beg != end)
    {
        total += *beg;
        ++beg;
    }

    return total;
}

TEST_CASE("accumulate function template works with generalized STL iterators")
{
    SECTION("raw pointers")
    {
        int nums[] = {1, 2, 3, 4, 5};
        auto sum = ::accumulate(nums, nums+5);

        REQUIRE(sum == 15);
    }

    SECTION("std::array")
    {
        auto nums = std::array<int, 5>{1, 2, 3, 4, 5};
        auto sum = ::accumulate(std::begin(nums), std::end(nums));

        REQUIRE(sum == 15);
    }

    SECTION("std::vector")
    {
        auto nums = std::vector{1, 2, 3, 4, 5};
        auto sum = ::accumulate(std::begin(nums), std::end(nums));

        REQUIRE(sum == 15);
    }
}