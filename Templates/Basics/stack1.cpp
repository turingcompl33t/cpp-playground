// stack1.cpp
// Demonstration of simple class template.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 stack1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

template <typename T>
class stack
{
    std::vector<T> m_elems;

public:
    void push(T const& elem);
    void pop();
    T const& top() const;

    bool empty() const
    {
        return m_elems.empty();
    }
};

template <typename T>
void stack<T>::push(T const& elem)
{
    m_elems.push_back(elem);
}

template <typename T>
void stack<T>::pop()
{
    assert(!m_elems.empty());
    m_elems.pop_back();
}

template <typename T>
T const& stack<T>::top() const
{
    assert(!m_elems.empty());
    return m_elems.back();
}

TEST_CASE("stack<int>")
{
    stack<int> int_stack{};

    REQUIRE(int_stack.empty());

    int_stack.push(11);
    int_stack.push(22);

    REQUIRE(!int_stack.empty());
    REQUIRE(int_stack.top() == 22);

    int_stack.pop();

    REQUIRE(int_stack.top() == 11);
}

TEST_CASE("stack<std::string>")
{
    stack<std::string> string_stack{};

    REQUIRE(string_stack.empty());

    string_stack.push("hello");
    string_stack.push("world");

    REQUIRE(!string_stack.empty());
    REQUIRE(string_stack.top() == "world");

    string_stack.pop();

    REQUIRE(string_stack.top() == "hello");
}