// unordered_map.cpp
// Demo of basic properties and usage of std::unordered_map.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <tuple>
#include <unordered_map>

class NonCopyable
{
public:
    NonCopyable() = default;

    NonCopyable(NonCopyable const&)            = delete;
    NonCopyable& operator=(NonCopyable const&) = delete;

    NonCopyable(NonCopyable&&)            = default;
    NonCopyable& operator=(NonCopyable&&) = default;
};

class Copyable
{
public:
    Copyable() = default;

    Copyable(Copyable const&)            = default;
    Copyable& operator=(Copyable const&) = default;

    Copyable(Copyable&&)            = default;
    Copyable& operator=(Copyable&&) = default;
};

class DummyAggregate 
{
public:
    int a{2};
    int b{3};
    NonCopyable c;
};

TEST_CASE("An aggregate type with a non-copyable member can be piecewise-constructed")
{
    std::pair<int, DummyAggregate> p{
        std::piecewise_construct, 
        std::forward_as_tuple(1), 
        std::forward_as_tuple()};

    REQUIRE(p.first == 1);
    REQUIRE(p.second.a == 2);
    REQUIRE(p.second.b == 3);
}

TEST_CASE("Piecewise construction can be used to emplace an aggregate with non-copyable member")
{
    std::unordered_map<int, DummyAggregate> map{};

    map.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(1),
        std::forward_as_tuple());

    REQUIRE(map[1].a == 2);
    REQUIRE(map[1].b == 3);    
}

class DummyAggregateV2
{
public:
    int a{2};
    int b{3};
    Copyable c;
};

TEST_CASE("All this nonsense is not needed in the event the aggregate does not contain a non-copyable member")
{
    std::unordered_map<int, DummyAggregateV2> map{};

    DummyAggregateV2 tmp{};
    map.emplace(1, tmp);

    REQUIRE(map[1].a == 2);
    REQUIRE(map[1].b == 3);
}
