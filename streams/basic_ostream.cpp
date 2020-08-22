// basic_ostream.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 basic_ostream.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <ostream>
#include <sstream>

TEST_CASE("std::basic_ostream<char>")
{    
    // same as std::ostream
    using stream_t = std::basic_ostream<char>;

    // initialize a std::stringbuf as the backing buffer for the output stream
    auto b = std::stringbuf{};

    // construct the stream; wraps the string buffer object
    auto s = stream_t{&b};

    // stream is in a good, working state
    REQUIRE(s.good());

    s << "hello";

    REQUIRE(s.tellp() == 5);
    REQUIRE(b.str() == "hello");
}

TEST_CASE("std::basic_ostream<wchar_t>")
{
    // same as std::wostream
    using stream_t = std::basic_ostream<wchar_t>;

    // initialize a std::wstringbuf as the backing buffer for the output stream
    auto b = std::wstringbuf{};

    // construct the stream, wraps the string buffer object
    auto s = stream_t{&b};

    // stream is in a good working state
    REQUIRE(s.good());

    s << L"hello";

    REQUIRE(s.tellp() == 5);
    REQUIRE(b.str() == L"hello");
}
