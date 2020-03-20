// unformatted_output.cpp
// Unformatted input operations with std::basic_ostream.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 unformatted_output.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <sstream>

TEST_CASE("")
{
    auto s = std::ostringstream{};

    // put() writes a single character to the stream
    s.put('h');
    REQUIRE(s.str() == "h");

    REQUIRE(s.tellp() == 1);

    // write() writes a specified number of characters to the stream
    s.write("ello", 4);
    REQUIRE(s.str() == "hello");

    REQUIRE(s.tellp() == 5);

    s.seekp(0);
    s.write("world", 5);
    REQUIRE(s.str() == "world");
}