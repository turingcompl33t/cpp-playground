// Reverse.cpp
// Demo of basic reverse iterator usage.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 Reverse.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <list>
#include <vector>

TEST_CASE("reverse iterators reverse the direction of iteration")
{
    const std::list<int> l{1, 2, 3};

    auto iter = l.rbegin();

    // slightly confusing semantics as we can immediately
    // dereference the reverse end iterator...
    REQUIRE(*iter == 3);
    ++iter;
    REQUIRE(*iter == 2);
    ++iter;
    REQUIRE(*iter == 1);
    ++iter;
    REQUIRE(iter == l.rend());
    // cannot dereference rend()
}

TEST_CASE("reverse iterators may be used to initialize containers")
{
    const std::vector<int> v1{1, 2, 3};
    const std::vector<int> v2{
        v1.rbegin(),
        v1.rend()
    };

    REQUIRE(v1[0] == 1);
    REQUIRE(v1[1] == 2);
    REQUIRE(v1[2] == 3);

    REQUIRE(v2[0] == 3);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 1);
}