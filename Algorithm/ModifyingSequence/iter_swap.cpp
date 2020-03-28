// iter_swap.cpp
//
// Demo of std::iter_swap()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 iter_swap.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>
#include <algorithm>

TEST_CASE("std::iter_swap()swaps the elements pointed to by two iterators")
{   
    auto c = std::vector<int>(5);
    std::iota(std::begin(c), std::end(c), 1);

    REQUIRE(c.front() == 1);
    REQUIRE(c.back() == 5);

    std::iter_swap(std::begin(c), --std::end(c));

    REQUIRE(c.front() == 5);
    REQUIRE(c.back() == 1);
}

template <typename Iter>
void selection_sort(Iter beg, Iter end)
{
    for (auto i = beg; i != end; ++i)
    {
        std::iter_swap(i, std::min_element(i, end));
    }
}

TEST_CASE("std::iter_swap() can be used to implement selection sort")
{
    auto c = std::vector<int>(10);
    std::iota(std::begin(c), std::end(c), 1);

    auto gen = std::mt19937{std::random_device{}()};

    std::shuffle(std::begin(c), std::end(c), gen);

    ::selection_sort(std::begin(c), std::end(c));

    REQUIRE(std::is_sorted(std::begin(c), std::end(c)));
}