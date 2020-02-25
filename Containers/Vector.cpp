// Vector.cpp
// Demo of basic properties and usage of std::vector.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 Vector.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <vector>
#include <utility>
#include <numeric>

TEST_CASE("std::vector supports default construction")
{
    std::vector<int> vec{};
    REQUIRE(vec.empty());
}

TEST_CASE("std::vector may be constructed with")
{
    SECTION("braced initializer (initializer list)")
    {
        std::vector<int> vec{5, 8};
        REQUIRE(vec[0] == 5);
        REQUIRE(vec[1] == 8);
    }

    SECTION("fill construction")
    {
        std::vector<int> vec(5, 8);
        REQUIRE(vec.size() == 5);
        REQUIRE(vec[0] == 8);
        REQUIRE(vec[4] == 8);
    }

    SECTION("iterators")
    {
        std::array<int, 4> array{0, 1, 2, 3};
        std::vector<int> vec(array.begin(), array.end());
        REQUIRE(vec.size() == array.size());
        REQUIRE(vec[0] == 0);
        REQUIRE(vec[1] == 1);
        REQUIRE(vec[2] == 2);
        REQUIRE(vec[3] == 3);
    }

    SECTION("copy construction")
    {
        std::vector<int> src{0, 1, 2, 3};
        std::vector<int> dst(src);
        
        REQUIRE(dst.size() == src.size());
        
        REQUIRE(dst[0] == src[0]);
        REQUIRE(dst[1] == src[1]);
        REQUIRE(dst[2] == src[2]);
        REQUIRE(dst[3] == src[3]);
    }

    SECTION("move construction")
    {
        std::vector<int> src{0, 1, 2, 3};
        std::vector<int> dst(std::move(src));
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
        std::vector<int> src{0, 1, 2, 3};
        std::vector<int> dst{4, 5, 6, 7};

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
        std::vector<int> src{0, 1, 2, 3};
        std::vector<int> dst{4, 5, 6, 7};

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
    std::vector<std::array<uint8_t, 1024>> kb_store{};
    REQUIRE(kb_store.max_size() > 0);
    REQUIRE(kb_store.empty());

    size_t elements{1024};
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
        std::vector<int> vec{0, 1, 2, 3};
        REQUIRE(vec.size() == 4);
        
        auto iter = vec.begin() + 2;
        vec.insert(iter, 99);

        REQUIRE(vec[2] == 99);
    }

    SECTION("push_back()")
    {
        std::vector<int> vec{0, 1, 2, 3};
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
        std::vector<std::pair<int, int>> vec{};
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
        std::vector<std::pair<int, int>> vec{};
        REQUIRE(vec.empty());

        vec.emplace_back(11, 22);
        REQUIRE(vec.size() == 1);
        REQUIRE(std::get<0>(vec.front()) == 11);
        REQUIRE(std::get<1>(vec.front()) == 22);
    }
}

TEST_CASE("std::vector supports the erase / remove idiom")
{
    std::vector<int> vec{0, 1, 2, 2, 3};

    REQUIRE(vec.size() == 5);

    vec.erase(std::remove(vec.begin(), vec.end(), 2), vec.end());

    REQUIRE(vec.size() == 3);
    REQUIRE(vec[0] == 0);
    REQUIRE(vec[1] == 1);
    REQUIRE(vec[2] == 3);
}

TEST_CASE("std::vector supports the erase / remove idiom with remove_if")
{
    std::vector<int> vec(10);
    std::iota(vec.begin(), vec.end(), 0);

    REQUIRE(vec.size() == 10);

    vec.erase(
        std::remove_if(vec.begin(), vec.end(), 
            [](int i){ return i % 2 == 0; }), 
        vec.end());

    REQUIRE(vec.size() == 5);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 3);
    REQUIRE(vec[2] == 5);
    REQUIRE(vec[3] == 7);
    REQUIRE(vec[4] == 9);
}