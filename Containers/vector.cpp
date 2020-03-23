// vector.cpp
// Demo of basic properties and usage of std::vector.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 vector.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <vector>
#include <utility>
#include <numeric>

TEST_CASE("std::vector supports default construction")
{
    auto vec = std::vector<int>{};
    REQUIRE(vec.empty());
}

TEST_CASE("std::vector may be constructed with")
{
    SECTION("braced initializer (initializer list)")
    {
        auto vec = std::vector<int>{5, 8};
        REQUIRE(vec[0] == 5);
        REQUIRE(vec[1] == 8);
    }

    SECTION("fill construction")
    {
        auto vec = std::vector<int>(5, 8);
        REQUIRE(vec.size() == 5);
        REQUIRE(vec[0] == 8);
        REQUIRE(vec[4] == 8);
    }

    SECTION("iterators")
    {
        auto array = std::array<int, 4>{0, 1, 2, 3};
        auto vec = std::vector<int>{array.begin(), array.end()};
        REQUIRE(vec.size() == array.size());
        REQUIRE(vec[0] == 0);
        REQUIRE(vec[1] == 1);
        REQUIRE(vec[2] == 2);
        REQUIRE(vec[3] == 3);
    }

    SECTION("copy construction")
    {
        auto src = std::vector<int>{0, 1, 2, 3};
        auto dst = std::vector<int>{src};
        
        REQUIRE(dst.size() == src.size());
        
        REQUIRE(dst[0] == src[0]);
        REQUIRE(dst[1] == src[1]);
        REQUIRE(dst[2] == src[2]);
        REQUIRE(dst[3] == src[3]);
    }

    SECTION("move construction")
    {
        auto src = std::vector<int>{0, 1, 2, 3};
        auto dst = std::vector<int>{std::move(src)};

        REQUIRE(dst.size() == 4);
        REQUIRE(dst[0] == 0);
        REQUIRE(dst[1] == 1);
        REQUIRE(dst[2] == 2);
        REQUIRE(dst[3] == 3);
    }
}

TEST_CASE("std::vector supports full copy / move semantics")
{
    SECTION("copy assignment")
    {
        auto src = std::vector<int>{0, 1, 2, 3};
        auto dst = std::vector<int>{4, 5, 6, 7};

        REQUIRE(dst[0] == 4);
        REQUIRE(dst[1] == 5);
        REQUIRE(dst[2] == 6);
        REQUIRE(dst[3] == 7);

        dst = src;

        REQUIRE(dst[0] == 0);
        REQUIRE(dst[1] == 1);
        REQUIRE(dst[2] == 2);
        REQUIRE(dst[3] == 3);
    }

    SECTION("move assignment")
    {
        auto src = std::vector<int>{0, 1, 2, 3};
        auto dst = std::vector<int>{4, 5, 6, 7};

        REQUIRE(dst[0] == 4);
        REQUIRE(dst[1] == 5);
        REQUIRE(dst[2] == 6);
        REQUIRE(dst[3] == 7);

        dst = std::move(src);

        REQUIRE(dst[0] == 0);
        REQUIRE(dst[1] == 1);
        REQUIRE(dst[2] == 2);
        REQUIRE(dst[3] == 3);
    }
}

TEST_CASE("std::vector exposes size management methods")
{
    auto kb_store = std::vector<std::array<uint8_t, 1024>>{};
    REQUIRE(kb_store.max_size() > 0);
    REQUIRE(kb_store.empty());

    auto elements = size_t{1024};
    kb_store.reserve(elements);
    REQUIRE(kb_store.empty());
    REQUIRE(kb_store.capacity() == elements);

    kb_store.emplace_back();
    kb_store.emplace_back();
    kb_store.emplace_back();
    REQUIRE(kb_store.size() == 3);

    kb_store.shrink_to_fit();
    REQUIRE(kb_store.capacity() >= 3);

    kb_store.clear();
    REQUIRE(kb_store.empty());
    REQUIRE(kb_store.capacity() >= 3);
}

TEST_CASE("std::vector supports element insertion with")
{
    SECTION("insert()")
    {
        auto vec = std::vector<int>{0, 1, 2, 3};
        REQUIRE(vec.size() == 4);
        
        auto iter = vec.begin() + 2;
        vec.insert(iter, 99);

        REQUIRE(vec[2] == 99);
    }

    SECTION("push_back()")
    {
        auto vec = std::vector<int>{0, 1, 2, 3};
        REQUIRE(vec.size() == 4);

        vec.push_back(77);
        REQUIRE(vec.size() == 5);
        REQUIRE(vec.back() == 77);

        vec.push_back(99);
        REQUIRE(vec.size() == 6);
        REQUIRE(vec.back() == 99);
    }

    SECTION("emplace()")
    {
        auto vec = std::vector<std::pair<int, int>>{};
        REQUIRE(vec.empty());

        vec.emplace(vec.begin(), 11, 22);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0].first == 11);
        REQUIRE(vec[0].second == 22);

        vec.emplace(vec.end(), 88, 99);
        REQUIRE(vec.size() == 2);
        REQUIRE(std::get<0>(vec.back()) == 88);
        REQUIRE(std::get<1>(vec.back()) == 99);
    }

    SECTION("emplace_back()")
    {
        auto vec = std::vector<std::pair<int, int>>{};
        REQUIRE(vec.empty());

        vec.emplace_back(11, 22);
        REQUIRE(vec.size() == 1);
        REQUIRE(std::get<0>(vec.front()) == 11);
        REQUIRE(std::get<1>(vec.front()) == 22);
    }
}

TEST_CASE("std::vector supports removing elements at a given position")
{
    SECTION("with a single iterator")
    {
        auto c = std::vector<int>{1, 2, 3};
        
        auto i1 = ++std::begin(c);

        REQUIRE(c.size() == 3);
        REQUIRE(*i1 == 2);

        c.erase(i1);  // iterator i is invalidated

        auto i2 = ++std::begin(c);

        REQUIRE(c.size() == 2);
        REQUIRE(*i2 == 3);
    }

    SECTION("with a range specified by iterators (half-open)")
    {
        auto c = std::vector<int>{1, 2, 3, 4, 5};

        auto beg = ++std::begin(c);
        auto end = beg + 3;

        REQUIRE(c.size() == 5);

        c.erase(beg, end);

        REQUIRE(c.size() == 2);
        REQUIRE(c == std::vector<int>{1, 5});
    }
}

template <typename T>
void erase(std::vector<T>& c, T const& val)
{
    c.erase(std::remove(std::begin(c), std::end(c), val), std::end(c));
}

TEST_CASE("std::vector supports removing elements equal to a specified value (erase-remove idiom)")
{
    SECTION("manually, in two distinct operations")
    {
        auto c = std::vector<int>{1, 2, 3};

        REQUIRE(c.size() == 3);

        // std::remove() reorders the elements of the vector such that
        // the removed element is now at the end of the vector (at or past c.end())
        auto it = std::remove(std::begin(c), std::end(c), 2);

        // the size is unchanged
        REQUIRE(c.size() == 3);

        // we can now use erase to actually remove and deallocate the element
        c.erase(it, std::end(c));

        REQUIRE(c.size() == 2);
    }

    SECTION("manually, in a single operation")
    {
        auto c = std::vector<int>{1, 2, 3};

        REQUIRE(c.size() == 3);

        // combine the two necessary calls
        c.erase(std::remove(std::begin(c), std::end(c), 2), std::end(c));

        REQUIRE(c.size() == 2);
    }

    SECTION("with a handy, custom wrapper")
    {
        auto c = std::vector<int>{1, 2, 3};

        REQUIRE(c.size() == 3);

        ::erase(c, 2);

        REQUIRE(c.size() == 2);
    }
}

template <typename T, typename Predicate>
void erase_if(std::vector<T>& c, Predicate pred)
{
    c.erase(std::remove_if(std::begin(c), std::end(c), pred), std::end(c));
}

TEST_CASE("std::vector supports removing elements that satisfy a predicate")
{
    auto is_even = [](int i){ return i%2 == 0; };

    SECTION("manually, in two distinct operations")
    {
        auto c = std::vector<int>{1, 2, 3};

        // just like std::remove(), returns an iterator
        auto it = std::remove_if(std::begin(c), std::end(c), is_even);

        REQUIRE(c.size() == 3);

        // now use the iterator from std::remove_f() to erase
        c.erase(it, std::end(c));

        REQUIRE(c.size() == 2);
    }

    SECTION("manually, in a single operation")
    {
        auto c = std::vector<int>{1, 2, 3};

        REQUIRE(c.size() == 3);

        c.erase(std::remove_if(std::begin(c), std::end(c), is_even), std::end(c));

        REQUIRE(c.size() == 2);
    }

    SECTION("with a handy, custom wrapper")
    {

    }
}

template <typename T>
void unique(std::vector<T>& c)
{
    if (!std::is_sorted(std::begin(c), std::end(c)))
    {
        std::sort(std::begin(c), std::end(c));
    }

    c.erase(std::unique(std::begin(c), std::end(c)), std::end(c));
}

TEST_CASE("std::vector supports removing duplicates")
{
    SECTION("which does not work if the duplicate elements are not consecutive")
    {
        auto c = std::vector<int>{1, 2, 3, 2};

        REQUIRE(c.size() == 4);

        c.erase(std::unique(std::begin(c), std::end(c)), std::end(c));

        // size unchanged!
        REQUIRE(c.size() == 4);
    }

    SECTION("but works as expected if the duplicates are consecutive")
    {
        auto c = std::vector<int>{1, 2, 3, 2};

        REQUIRE(c.size() == 4);

        std::sort(std::begin(c), std::end(c));
        c.erase(std::unique(std::begin(c), std::end(c)), std::end(c));

        REQUIRE(c.size() == 3);
    }

    SECTION("and is simplified by a handy utility function")
    {
        auto c1 = std::vector<int>{1, 2, 2, 3};
        auto c2 = std::vector<int>{1, 2, 3, 2};

        ::unique(c1);
        ::unique(c2);

        REQUIRE(c1.size() == 3);
        REQUIRE(c2.size() == 3);
        REQUIRE(c1 == c2);
    }
}