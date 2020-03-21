// streambuf.cpp
// Basic operations with boost::asio::streambuf.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 /I C:\Dev\Boost streambuf.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define BOOST_ALL_NO_LIB

#include <boost/asio.hpp>

namespace net = boost::asio;

TEST_CASE("boost::asio::streambuf with manual consume()")
{
    auto buffer = net::streambuf{};

    auto ostream = std::ostream{&buffer};
    ostream << "hello";

    REQUIRE(buffer.size() == 5);

    buffer.consume(5);

    REQUIRE(buffer.size() == 0);
}

TEST_CASE("boost::asio::streambuf with both input and output streams")
{
    auto buffer = net::streambuf{};

    auto ostream = std::ostream{&buffer};
    auto istream = std::istream{&buffer};

    // output stream writes characters to buffer
    ostream << "hello";

    REQUIRE(buffer.size() == 5);

    // input stream reads and consumes characters from the buffer
    auto s = std::string{};
    istream >> s;

    REQUIRE(s == "hello");
    REQUIRE(buffer.size() == 0);
}