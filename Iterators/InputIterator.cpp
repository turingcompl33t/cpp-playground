// InputIterator.cpp
// Demo of basic input iterator usage.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 InputIterator.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <forward_list>

TEST_CASE("std::forward_list begin() and end() provide input iterators")
{
    const std::forward_list<int> fl{1, 2, 3};
    
    auto iter = fl.begin();

    REQUIRE(*iter == 1);
    ++iter;
    REQUIRE(*iter == 2);
    ++iter;
    REQUIRE(*iter == 3);
    ++iter;
    REQUIRE(iter == fl.end());
}