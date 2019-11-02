// Factorial.cpp
// Compile-time factorial calculator using TMP.
//
// This is an example of a template that calculates a value, 
// as opposed to one that unrolls loops or specializes a function.

#include <iostream>

// the recursive case 
template<int N>
struct Factorial
{
    static int const Result{ N * Factorial<N - 1>::Result };
};

// the base case (specialization)
template<>
struct Factorial<1>
{
    static int const Result { 1 };
};

// why "static const" for the Result member above?
// the member must be static because we aren't actually 
// instantiating any class instances (all of the computation is compile-time)
// the member must be const to reflect the fact that the value in
// question is and must be resolvable at compile time

int main()
{
    // prints 120
    std::cout << Factorial<5>::Result << std::endl;
}