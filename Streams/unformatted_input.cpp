// unformatted_input.cpp
// Unformatted input operations with std::basic_istream.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 unformatted_input.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <sstream>

TEST_CASE("unformatted operations with std::basic_istream")
{
    auto s = std::istringstream{"hello world"};

    // stream starts at initial position (duh)
    REQUIRE(s.tellg() == 0);

    // get() without argument simply returns the first character
    REQUIRE(s.get() == 'h');

    // the character is not consumed
    REQUIRE(s.str() == "hello world");
    // but the stream position is advanced
    REQUIRE(s.tellg() == 1);

    // the get(char) overload just places the read character in the passed char
    char c;
    s.get(c);
    REQUIRE(c == 'e');
    REQUIRE(s.tellg() == 2);

    // an additional overload of get(char*, count) allows extraction of strings
    char buffer[4];
    s.get(buffer, 5);  // reads count - 1 characters into buffer

    REQUIRE(s.tellg() == 6);  // "world"

    // the peek() function lets use look at the next character in the stream
    // without advancing the stream's internal cursor
    REQUIRE(s.peek() == 'w');

    // the unget() function puts the last read character back into the stream
    REQUIRE(s.get() == 'w');
    REQUIRE(s.tellg() == 7);
    s.unget();
    REQUIRE(s.peek() == 'w');
    REQUIRE(s.tellg() == 6);

    // the ignore() function allows us to extract and discard a specified number of characters
    // by specifying the maximum possible value for the stream size, we effectively
    // ignore all of the characters remaining in the stream
    s.ignore(std::numeric_limits<std::streamsize>::max());

    // the gcount() function tells us the number of characters consumer by
    // the preceding unformatted input operation
    REQUIRE(s.gcount() == 5);  // consumed "world"
}