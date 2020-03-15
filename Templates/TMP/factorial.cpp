// factorial.cpp
// Compile-time factorial calculator using TMP.
//
// This is an example of a template that calculates a value, 
// as opposed to one that unrolls loops or specializes a function.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I C:\Dev\Catch2 factorial.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

// the recursive case 
template<int N>
struct factorial
{
    static int const result{ N * factorial<N - 1>::result };
};

// the base case (specialization)
template<>
struct factorial<1>
{
    static int const result { 1 };
};

// why "static const" for the Result member above?
// the member must be static because we aren't actually 
// instantiating any class instances (all of the computation is compile-time)
// the member must be const to reflect the fact that the value in
// question is and must be resolvable at compile time

TEST_CASE("factorial is computed at compile time")
{
    REQUIRE(factorial<5>::result == 120);
}