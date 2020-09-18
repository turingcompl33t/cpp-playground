// heap.cpp
// The STL heap API with std::vector as underlying container.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <numeric>
#include <algorithm>

TEST_CASE("std::make_heap and std::pop_heap implement a max heap by default")
{
    auto const HEAP_SIZE = 10;

    auto v = std::vector<int>(HEAP_SIZE);
    std::iota(std::begin(v), std::end(v), 1);

    REQUIRE(v.size() == HEAP_SIZE);

    std::make_heap(std::begin(v), std::end(v));

    while (v.size() > 0)
    {
        std::pop_heap(std::begin(v), std::end(v));
        
        auto const expected = v.size();
        auto const popped   = v.back();

        REQUIRE(popped == static_cast<int>(expected));

        v.pop_back();
    }

    REQUIRE(v.size() == 0);
}

TEST_CASE("a custom comparator can be provided to implement a min heap")
{
    auto const HEAP_SIZE = 10;

    auto v = std::vector<int>(HEAP_SIZE);
    std::iota(std::begin(v), std::end(v), 1);

    REQUIRE(v.size() == HEAP_SIZE);

    std::make_heap(std::begin(v), std::end(v), std::greater<int>{});

    while (v.size() > 0)
    {
        std::pop_heap(std::begin(v), std::end(v), std::greater<int>{});
        
        auto const expected = HEAP_SIZE - v.size() + 1;
        auto const popped   = v.back();

        REQUIRE(popped == static_cast<int>(expected));

        v.pop_back();
    }

    REQUIRE(v.size() == 0);
}