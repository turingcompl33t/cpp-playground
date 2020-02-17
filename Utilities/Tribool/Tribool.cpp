// Tribool.cpp
// Demo of boost::tribool.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Boost /I c:\Dev\Catch Tribool.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iostream>
#include <boost/logic/tribool.hpp>

using boost::logic::indeterminate;

boost::logic::tribool tribool_t = true;
boost::logic::tribool tribool_f = false;
boost::logic::tribool tribool_i = indeterminate;

TEST_CASE("boost::tribool converts to bool")
{
    REQUIRE(tribool_t);
    REQUIRE_FALSE(tribool_f);

    REQUIRE(!tribool_f);
    REQUIRE_FALSE(!tribool_t);

    REQUIRE(indeterminate(tribool_i));
    REQUIRE_FALSE(indeterminate(tribool_t));
}

TEST_CASE("boost::tribool supports standard boolean operations")
{
    auto t_or_f = tribool_t || tribool_f;
    REQUIRE(t_or_f);
    REQUIRE(indeterminate(tribool_t && tribool_i));
    REQUIRE(indeterminate(tribool_f || tribool_i));
    REQUIRE(indeterminate(!tribool_i));
}

TEST_CASE("boost::tribool works nicely with conditional logic")
{
    if (tribool_i) FAIL("indeterminate is true");           // only evaulates if i is true
    else if (!tribool_i) FAIL("indeterminate is false");    // only evaluates if i is false
    else {}                                                 // i is indeterminate
}