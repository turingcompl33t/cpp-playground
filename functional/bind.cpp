// bind.cpp
// Basic usage of std::bind.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 bind.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <functional>

long multiply(long a, long b)
{
    return a*b;
}

TEST_CASE("std::bind supports binding free functions")
{
    SECTION("with fully applied function")
    {
        auto fn = std::bind(multiply, 2, 10);
        
        auto result = fn();
        REQUIRE(result == 20);
    }

    SECTION("with partially applied function")
    {
        auto times_ten = std::bind(multiply, std::placeholders::_1, 10);
        auto times_two = std::bind(multiply, 2, std::placeholders::_1);

        REQUIRE(times_ten(2) == 20);
        REQUIRE(times_two(10) == 20);
    }
}

struct Computer
{
    long m_a;
    long m_b;

    Computer(long a, long b) : m_a{a}, m_b{b} {}

    long multiply()
    {
        return m_a*m_b;
    }

    long sum(long c)
    {
        return m_a+m_b+c;
    }
};

TEST_CASE("std::bind suports binding member functions")
{
    SECTION("with fully applied function")
    {
        auto c = Computer{2, 10};

        auto fn = std::bind(&Computer::multiply, std::placeholders::_1);
        REQUIRE(fn(c) == 20);
    }

    SECTION("with partially applied function")
    {
        auto c = Computer{2, 10};

        auto fn = std::bind(&Computer::sum, c, std::placeholders::_1);
        REQUIRE(fn(8) == 20);
    }
}

TEST_CASE("std::bind supports composition of STL function objects")
{
    using namespace std::placeholders;

    SECTION("simple case")
    {
        auto plus10 = std::bind(std::plus<int>{}, _1, 10);

        REQUIRE(plus10(2) == 12);
    }

    SECTION("with nesting")
    {
        auto plus10times2 = std::bind(
            std::multiplies<int>{},
                std::bind(std::plus<int>{}, _1, 10),
                2
            );

        auto r = plus10times2(2);
        REQUIRE(r == 24);
    }
}
