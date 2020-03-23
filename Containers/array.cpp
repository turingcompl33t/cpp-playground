// array.cpp
// Demo of basic properties and usage of std::array.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 array.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <utility>

// statically allocated array, no braced initializer
std::array<int, 4> static_array;

TEST_CASE("std::array construction")
{
    SECTION("statically allocated std::array without braced initialization is zero-initialized")
    {
        REQUIRE(static_array[0] == 0);
    }

    SECTION("locally allocated std:array with braced initialization is zero-initialized")
    {
        std::array<int, 4> array{};
        REQUIRE(array[0] == 0);
    }

    SECTION("locally allocated std::array with init list gets remaining elements zero-initialized")
    {
        std::array<int, 10> array{1, 2, 3, 4};
        REQUIRE(array[0] == 1);
        REQUIRE(array[1] == 2);
        REQUIRE(array[2] == 3);
        REQUIRE(array[3] == 4);
        REQUIRE(array[4] == 0);
        // ...
        REQUIRE(array[9] == 0);
    }
}

TEST_CASE("std::array access")
{
    std::array<int, 4> array{0, 1, 2, 3};

    SECTION("operator[] can get and set elements")
    {
        REQUIRE(array[2] == 2);
        array[2] = 99;
        REQUIRE(array[2] == 99);
    }

    SECTION("at() can get and set elements")
    {
        REQUIRE(array[2] == 2);
        array.at(2) = 99;
        REQUIRE(array.at(2) == 99);

        // runtime bounds checking
        REQUIRE_THROWS_AS(array.at(4), std::out_of_range);
    }

    SECTION("std::get() can get and set elements")
    {
        REQUIRE(array[2] == 2);
        REQUIRE(std::get<2>(array) == 2);
        std::get<2>(array) = 99;
        REQUIRE(std::get<2>(array) == 99);

        // compile-time bounds checking; fails to compile
        // std::get<4>(array)
    }
}

TEST_CASE("std::array convenience methods")
{
    std::array<int, 4> array{0, 1, 2, 3};

    SECTION("font()")
    {
        REQUIRE(array[0] == 0);
        array.front() = 99;
        REQUIRE(array.front() == 99);
        REQUIRE(array.front() == array[0]);
    }

    SECTION("back()")
    {
        REQUIRE(array[0] == 0);
        array.back() = 99;
        REQUIRE(array.back() == 99);
        REQUIRE(array.back() == array[3]);
    }
}

TEST_CASE("std::array provides ability to access underlying raw array with")
{
    std::array<int, 4> array{11, 22, 33, 44};

    SECTION("data()")
    {
        auto const front_ptr = array.data();
        REQUIRE(*front_ptr == 11);
    }

    SECTION("address-of front")
    {
        auto const front_ptr = array.data();
        REQUIRE(&array.front() == front_ptr);
    }

    SECTION("address-of at(0)")
    {
        auto const front_ptr = array.data();
        REQUIRE(&array.at(0) == front_ptr);
    }

    SECTION("address-of [0]")
    {
        auto const front_ptr = array.data();
        REQUIRE(&array[0] == front_ptr);
    }
}

TEST_CASE("std::array provides some useful utility methods")
{
    SECTION("size() and max_size() are identical for std::array")
    {
        std::array<int, 4> array{1, 2, 3, 4};
        REQUIRE(array.size() == 4);
        REQUIRE(array.max_size() == 4);
    }

    SECTION("fill() fills the std::array with specified value")
    {
        std::array<int, 4> array{};
        array.fill(3);
        REQUIRE(array[0] == 3);
        REQUIRE(array[1] == 3);
        REQUIRE(array[2] == 3);
        REQUIRE(array[3] == 3);
    }

    SECTION("swap() exchanges the contents of two arrays")
    {
        std::array<int, 4> a1{10, 11, 12, 13};
        std::array<int, 4> a2{20, 21, 22, 23};

        REQUIRE(a1[0] == 10);
        REQUIRE(a2[0] == 20);

        a1.swap(a2);

        REQUIRE(a1[0] == 20);
        REQUIRE(a2[0] == 10);

        std::swap(a1, a2);

        REQUIRE(a1[0] == 10);
        REQUIRE(a2[0] == 20);
    }
}