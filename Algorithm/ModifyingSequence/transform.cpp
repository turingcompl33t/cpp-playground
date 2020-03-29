// transform.cpp
//
// Demo of std::transform()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 transform.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <tuple>
#include <vector>
#include <numeric>
#include <algorithm>
#include <execution>

TEST_CASE("std::transform()")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 0);  // 0 - 9

    // squares all the elements in c
    std::transform(c.begin(), c.end(), c.begin(), 
        [](int const i) -> int { return i*i; });

    REQUIRE(c.size() == 10);
    REQUIRE(c.back() == 81);
}

template <typename Iter1, typename Iter2, typename Iter3>
void zip(Iter1 beg1, Iter1 end1, Iter2 beg2, Iter3 beg3)
{
    std::transform(beg1, end1, beg2, beg3, 
        [](auto& e1, auto& e2)
        {
            return std::make_pair(e1, e2);
        });
}

TEST_CASE("std::transform() can be used to implement zip-like functionality")
{
    SECTION("common element type")
    {
        auto c1 = std::vector<int>(5);
        auto c2 = std::vector<int>(5);

        std::iota(std::begin(c1), std::end(c1), 1);  // 1 - 5 
        std::iota(std::begin(c2), std::end(c2), 6);  // 6 - 10

        auto r = std::vector<std::pair<int, int>>{};

        ::zip(
            std::begin(c1), 
            std::end(c1), 
            std::begin(c2), 
            std::back_inserter(r));

        REQUIRE(r.size() == 5);
        REQUIRE(r[0] == std::pair<int, int>{1, 6});
        REQUIRE(r[4] == std::pair<int, int>{5, 10});
    }

    SECTION("distinct element types")
    {
        auto c1 = std::vector<int>(5);
        auto c2 = std::vector<std::string>(5);

        std::iota(std::begin(c1), std::end(c1), 1);

        auto i = 1;
        std::generate(std::begin(c2), std::end(c2), 
            [&i](){ return std::to_string(i++); });

        auto r = std::vector<std::pair<int, std::string>>{};

        ::zip(
            std::begin(c1), 
            std::end(c1),
            std::begin(c2),
            std::back_inserter(r));

        REQUIRE(r.size() == 5);

        REQUIRE(r[0].first == 1);
        REQUIRE(r[0].second == "1");

        REQUIRE(r[4].first == 5);
        REQUIRE(r[4].second == "5");
    }
}

TEST_CASE("std::transform() can be used with a parallel execution policy")
{
    auto c = std::vector<int>(10);
    std::iota(std::begin(c), std::end(c), 1); // 1 - 10

    // NOTE: wanted to default construct r here and use 
    // a back_insert_iterator to output transform results 
    // to the result vector, but the parallel_policy requires 
    // forward_iterators or "stronger" - got a nice compile error

    auto r = std::vector<int>(10);

    std::transform(
        std::execution::par,
        std::begin(c), std::end(c),
        std::begin(r),
        [](int i)
        {
            return i*2;
        });

    auto c_sum = std::accumulate(std::begin(c), std::end(c), 0);
    auto r_sum = std::accumulate(std::begin(r), std::end(r), 0);

    REQUIRE(r_sum == 2*c_sum);
}