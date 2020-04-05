// coupling1.cpp
// Demo of strong stream coupling via stream buffer sharing.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 coupling1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <sstream>
#include <streambuf>

TEST_CASE("")
{
    auto b = std::stringbuf{};

    // streams s1 and s2 share underlying stream buffer
    auto s1 = std::ostream{&b};
    auto s2 = std::ostream{s1.rdbuf()};
    
    s1 << "hello";
    s2 << " world";

    REQUIRE(b.str() == "hello world");
}