// basics.cpp
// 
// Demo of basic exception handling in C++
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 basics.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <stdexcept>

class catastrophic_failure
    : public std::runtime_error
{
public:
    catastrophic_failure(std::string const& what_msg)
        : std::runtime_error{what_msg}
    {}

    //const char* what() const noexcept override;
};

int intense_compututation()
{
    // do stuff

    throw catastrophic_failure{"Computation Failed!"};

    // maybe do other stuff
}

TEST_CASE("throwing and catching custom exception classes")
{
    SECTION("letting catch swallow the exception")
    {
        REQUIRE_THROWS_AS(intense_compututation(), catastrophic_failure);
    }

    SECTION("catching the exception ourselves")
    {
        try
        {
            intense_compututation();
        }
        catch (catastrophic_failure const& f)
        {
            // hopefully string ctor doesn't throw...
            auto tmp = std::string{f.what()};
            REQUIRE(tmp == "Computation Failed!");
        }
    }
}