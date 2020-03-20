// overload_inserter.cpp
// Demonstration of basic operator<< overloading.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 overload_inserter.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <sstream>

class producer
{
    std::string m_str;
public:
    producer(std::string const& str) : m_str{ str }
    {}

    friend std::ostream& operator<<(std::ostream& stream, producer const& p)
    {
        stream << p.m_str;
        return stream;
    }
};

TEST_CASE("overloading operator<< for a custom type")
{
    auto s = std::ostringstream{};
    auto p = producer{"hello world"};

    // stream custom type into stringstream
    s << p;

    REQUIRE(s.str() == "hello world");
}