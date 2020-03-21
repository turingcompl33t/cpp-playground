// accum3.cpp
// Using templates with traits types for customization points.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 accum3.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

template <typename T>
struct AccumulationTraits;

template <>
struct AccumulationTraits<char>
{
    using AccT = int;
    static AccT const zero = 0;
};

template <>
struct AccumulationTraits<short>
{
    using AccT = int;
    static AccT const zero = 0;
};

template <>
struct AccumulationTraits<int>
{
    using AccT = long;
    static AccT const zero = 0;
};

template <>
struct AccumulationTraits<unsigned int>
{
    using AccT = unsigned long;
    static AccT const zero = 0;
};

template <>
struct AccumulationTraits<float>
{
    using AccT = double;
    static constexpr AccT const zero = 0.0;
};

template <typename T>
auto accumulate(T const* beg, T const* end)
{
    using AccT = AccumulationTraits<T>::AccT;

    AccT total = AccumulationTraits<T>::zero;
    while (beg != end)
    {
        total += *beg;
        ++beg;
    }

    return total;
}

TEST_CASE("accumulation function template works with integer collection")
{
    int num[] = {1, 2, 3, 4, 5};
    auto sum = ::accumulate(num, num+5);

    REQUIRE(sum == 15);
}

TEST_CASE("accumulation function template works with character collection")
{
    char name[] = "hello";   
    auto length = sizeof(name) - 1;

    auto sum = ::accumulate(name, name+length);

    // 532 is sum of ASCII decimals
    REQUIRE(sum == 532);
}

TEST_CASE("accumulation function template works with floating point collection")
{
    float vals[] = {1.0, 2.0, 3.0};
    auto sum = ::accumulate(vals, vals+3);

    REQUIRE(sum == 6.0);
}