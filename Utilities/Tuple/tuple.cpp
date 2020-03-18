// tuple.cpp
// Demo of std::tuple.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 tuple.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <utility>

struct X
{
    X(int id) : m_id{ id }
    {}

    int get_id() const noexcept
    {
        return m_id;
    }
private:
    int const m_id;
};

struct Y
{
    Y(int id) : m_id{ id }
    {}

    int get_id() const noexcept
    {
        return m_id;
    }
private:
    int const m_id;
};

struct Z
{
    Z(int id) : m_id{ id }
    {}

    int get_id() const noexcept
    {
        return m_id;
    }
private:
    int const m_id;
};

std::tuple<int, int, int> some_function()
{
    return std::make_tuple(1, 2, 3);
}

TEST_CASE("std::tuple permits access to members with std::get")
{
    using triple = std::tuple<X, Y, Z>;

    auto x = X{1};
    auto y = Y{2};
    auto z = Z{3};

    auto trio = triple{1, 2, 3};

    REQUIRE(std::get<0>(trio).get_id() == x.get_id());
    REQUIRE(std::get<X>(trio).get_id() == x.get_id());

    REQUIRE(std::get<1>(trio).get_id() == y.get_id());
    REQUIRE(std::get<Y>(trio).get_id() == y.get_id());

    REQUIRE(std::get<2>(trio).get_id() == z.get_id());
    REQUIRE(std::get<Z>(trio).get_id() == z.get_id());
}

TEST_CASE("std::tuple (with C++14) supports accessing members with std::tie()")
{
    int x, y, z;
    std::tie(x, y, z) = some_function();

    REQUIRE(x == 1);
    REQUIRE(y == 2);
    REQUIRE(z == 3);
}

TEST_CASE("std::tuple (with C++17) supports structured bindings")
{
    auto [x, y, z] = some_function();

    REQUIRE(x == 1);
    REQUIRE(y == 2);
    REQUIRE(z == 3);
}