// deque.cpp
// Demo of basic properties and usage of std::deque.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 deque.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <deque>

TEST_CASE("std::deque supports removing elements by position")
{
    SECTION("with a single positon")
    {
        auto c = std::deque<int>{1, 2, 3};

        REQUIRE(c.size() == 3);

        auto i = ++std::begin(c);
        c.erase(i);

        REQUIRE(c.size() == 2);
    }

    SECTION("with a range specified by begin and end iterators")
    {
        auto c = std::deque<int>{1, 2, 3, 4, 5};

        REQUIRE(c.size() == 5);

        auto beg = ++std::begin(c);
        auto end = beg + 3;

        c.erase(beg, end);

        REQUIRE(c.size() == 2); // {1, 5}
    }
}

template <typename T>
void erase(std::deque<T>& c, T const& val)
{
    c.erase(std::remove(std::begin(c), std::end(c), val), std::end(c));
}

TEST_CASE("std::deque supports removing items by value")
{
    SECTION("manually, in two distinct operations")
    {
        auto c = std::deque<int>{1, 2, 3};

        auto it = std::remove(std::begin(c), std::end(c), 2);

        // size unchanged
        REQUIRE(c.size() == 3);

        c.erase(it, std::end(c));

        // now gone
        REQUIRE(c.size() == 2);
    }

    SECTION("manually, in a single operation")
    {
        auto c = std::deque<int>{1, 2, 3};

        REQUIRE(c.size() == 3);

        c.erase(std::remove(std::begin(c), std::end(c), 2), std::end(c));

        REQUIRE(c.size() == 2);
    }

    SECTION("with the help of a handy wrapper function")
    {
        auto c = std::deque<int>{1, 2, 3};

        REQUIRE(c.size() == 3);

        ::erase(c, 2);

        REQUIRE(c.size() == 2);
    }
}

template <typename T, typename Predicate>
void erase_if(std::deque<T>& c, Predicate pred)
{
    c.erase(std::remove_if(std::begin(c), std::end(c), pred), std::end(c));
}

TEST_CASE("std::deque supports removing elements that satisfy a predicate")
{
    auto is_even = [](int i){ return i%2 == 0 ;};

    SECTION("manually, with two distinct operations")
    {
        auto c = std::deque<int>{1, 2, 3};

        auto it = std::remove_if(std::begin(c), std::end(c), is_even);

        REQUIRE(c.size() == 3);

        c.erase(it, std::end(c));

        REQUIRE(c.size() == 2);
    }

    SECTION("manually, with a single operation")
    {
        auto c = std::deque<int>{1, 2, 3};

        REQUIRE(c.size() == 3);

        c.erase(std::remove_if(std::begin(c), std::end(c), is_even), std::end(c));

        REQUIRE(c.size() == 2);
    }

    SECTION("with the help of a handy wrapper function")
    {
        auto c = std::deque<int>{1, 2, 3};

        REQUIRE(c.size() == 3);

        ::erase_if(c, is_even);

        REQUIRE(c.size() == 2);
    }
}

template <typename T>
void unique(std::deque<T>& c)
{
    if (!std::is_sorted(std::begin(c), std::end(c)))
    {
        std::sort(std::begin(c), std::end(c));
    }

    c.erase(std::unique(std::begin(c), std::end(c)), std::end(c));
}

TEST_CASE("std::deque supports removing duplicate elements")
{
    SECTION("which does not work if the duplcates are not consecutive")
    {
        auto c = std::deque<int>{1, 2, 3, 2};

        REQUIRE(c.size() == 4);

        c.erase(std::unique(std::begin(c), std::end(c)), std::end(c));

        // size unchanged!
        REQUIRE(c.size() == 4);
    }

    SECTION("but works as expected if the duplicates are consecutive")
    {
        auto c = std::deque<int>{1, 2, 2, 3};

        REQUIRE(c.size() == 4);

        std::sort(std::begin(c), std::end(c));
        c.erase(std::unique(std::begin(c), std::end(c)), std::end(c));

        // element removed
        REQUIRE(c.size() == 3);
    }

    SECTION("and makes for a handy wrapper function")
    {
        auto c1 = std::deque<int>{1, 2, 2, 3};
        auto c2 = std::deque<int>{1, 2, 3, 2};

        ::unique(c1);
        ::unique(c2);

        REQUIRE(c1.size() == 3);
        REQUIRE(c2.size() == 3);
        REQUIRE(c1 == c2);
    }
}