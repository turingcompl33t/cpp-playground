// stacknontype.cpp
// Slightly more generic version of stacknontype wherin the
// nontype template parameter used to specify the max size of the
// stack is of generic type by using auto in template parameter list.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 stackauto.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <string>
#include <cstddef>

template <typename T, auto max_size>
class stack
{
    using count_type = decltype(max_size);

    std::array<T, max_size> m_elems;
    count_type              m_count;  // current number of elements

public:
    stack() : m_count{0} {}
    void push(T const& e);
    void pop();
    T const& top();

    bool empty() const
    {
        return 0 == m_count;
    }

    count_type count() const
    {
        return m_count;
    }
};

template <typename T, auto max_size>
void stack<T, max_size>::push(T const& e)
{
    assert(m_count < max_size);
    m_elems[m_count++] = e;
}

template <typename T, auto max_size>
void stack<T, max_size>::pop()
{
    assert(m_count > 0);
    m_count--;
}

template <typename T, auto max_size>
T const& stack<T, max_size>::top()
{
    assert(m_count > 0);
    return m_elems[m_count - 1];
}

TEST_CASE("stack implementation with array as backing storage works as expected")
{
    SECTION("with primitive types")
    {
        // count_type is int
        auto s = stack<int, 20>{};

        REQUIRE(s.empty());
        REQUIRE(s.count() == 0);
        REQUIRE(std::is_same_v<decltype(s.count()), int>);

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
        // count_type is int
        auto s = stack<std::string, 20>{};

        REQUIRE(s.empty());
        REQUIRE(s.count() == 0);
        REQUIRE(std::is_same_v<decltype(s.count()), int>);

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

TEST_CASE("stack implementation supports various types for nontype parameter")
{
    // count_type is unsigned long
    auto s1 = stack<int, 10ul>{};
    REQUIRE(std::is_same_v<decltype(s1.count()), unsigned long>);

    // count_type is int
    auto s2 = stack<int, 10>{}; 
    REQUIRE(std::is_same_v<decltype(s2.count()), int>);

    // the return types of count() for the two stacks are distinct
    REQUIRE_FALSE(std::is_same_v<
                    decltype(s1.count()), 
                    decltype(s2.count())>
                    );
}
