// stacknontype.cpp
// Demo of nontype template parameters; implemeting stack with
// fixed size specified by nontype template parameter.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 stacknontype.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <string>
#include <cstddef>

template <typename T, std::size_t max_size>
class stack
{
    std::array<T, max_size> m_elems;
    std::size_t             m_count;  // current number of elements

public:
    stack() : m_count{0} {}
    void push(T const& e);
    void pop();
    T const& top();

    bool empty() const
    {
        return 0 == m_count;
    }

    std::size_t count() const
    {
        return m_count;
    }
};

template <typename T, std::size_t max_size>
void stack<T, max_size>::push(T const& e)
{
    assert(m_count < max_size);
    m_elems[m_count++] = e;
}

template <typename T, std::size_t max_size>
void stack<T, max_size>::pop()
{
    assert(m_count > 0);
    m_count--;
}

template <typename T, std::size_t max_size>
T const& stack<T, max_size>::top()
{
    assert(m_count > 0);
    return m_elems[m_count - 1];
}

TEST_CASE("stack implementation with array as backing storage works as expected")
{
    SECTION("with primitive types")
    {
        auto s = stack<int, 20>{};

        REQUIRE(s.empty());
        REQUIRE(s.count() == 0);

        s.push(1);
        REQUIRE(!s.empty());
        REQUIRE(s.count() == 1);

        s.push(2);
        REQUIRE(s.count() == 2);

        REQUIRE(s.top() == 2);

        s.pop();

        REQUIRE(s.count() == 1);
        REQUIRE(s.top() == 1);

        s.pop();

        REQUIRE(s.empty());
    }

    SECTION("with class types")
    {
        auto s = stack<std::string, 20>{};

        REQUIRE(s.empty());
        REQUIRE(s.count() == 0);

        s.push("hello");
        REQUIRE(!s.empty());
        REQUIRE(s.count() == 1);

        s.push("world");
        REQUIRE(s.count() == 2);

        REQUIRE(s.top() == "world");

        s.pop();

        REQUIRE(s.count() == 1);
        REQUIRE(s.top() == "hello");

        s.pop();

        REQUIRE(s.empty());
    }
}
