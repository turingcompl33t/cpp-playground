// null.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 null.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <stdexcept>
#include <memory_resource>

TEST_CASE("allocate() for null_memory_resource throws std::bad_alloc")
{
    auto null_alloc = std::pmr::null_memory_resource();

    REQUIRE_THROWS_AS(null_alloc->allocate(0), std::bad_alloc);
}

TEST_CASE("std::vector::push_back() throws when constructed with null allocator")
{
    auto null_alloc = std::pmr::null_memory_resource();

    auto c = std::pmr::vector<int>{null_alloc};

    REQUIRE_THROWS_AS(c.push_back(1), std::bad_alloc);
}