// accum5.cpp
// Using templates with traits types for customization points.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 accum5.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

template <typename T>
struct AccumulationTraits;

template <>
struct AccumulationTraits<char>
{
    using AccT = int;
};

template <>
struct AccumulationTraits<short>
{
    using AccT = int;
};

template <>
struct AccumulationTraits<int>
{
    using AccT = long;
};

template <>
struct AccumulationTraits<unsigned int>
{
    using AccT = unsigned long;
};

template <>
struct AccumulationTraits<float>
{
    using AccT = double;
};

class SumPolicy
{
public:
    template <typename T1, typename T2>
    static void accumulate(T1& total, T2& value)
    {
        total += value;
    }
};

class MultPolicy
{
public:
    template <typename T1, typename T2>
    static void accumulate(T1& total, T2& value)
    {
        total *= value;
    }
};

template <typename T, 
          typename Policy = SumPolicy,
          typename Traits = AccumulationTraits<T>>
auto accumulate(
    T const* beg, 
    T const* end, 
    typename Traits::AccT init
    )
{
    using AccT = typename Traits::AccT;
    AccT total = init;
    
    while (beg != end)
    {
        Policy::accumulate(total, *beg);
        ++beg;
    }

    return total;
}

TEST_CASE("accumulation function template works with sum policy")
{
    int nums[] = {1, 2, 3, 4, 5};
    auto sum = ::accumulate(nums, nums+5, 0);

    REQUIRE(sum == 15);
}

TEST_CASE("accumulation function template works with mulitplication policy")
{
    int nums[] = {1, 2, 3, 4, 5};
    auto product = ::accumulate<int, MultPolicy>(nums, nums+5, 1);

    REQUIRE(product == 120);
}