// new.cpp
//
// Some C++ memory model distinctions.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 new.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <new>

struct X
{
    int m_a;
    int m_b;

    X(int a, int b) : m_a{a}, m_b{b}
    {}
};

TEST_CASE("the new keyword combines the functionality of operator new \
    and a placement new operations")
{
    // using new expression directly
    X* x1 = ::new X{1, 2};

    // is equivalent to this two-step process:
    // allocation, then construction
    void* addr = ::operator new(sizeof(X));
    X* x2 = ::new (addr) X{3, 4};


    REQUIRE(x1->m_a == 1);
    REQUIRE(x1->m_b == 2);
    REQUIRE(x2->m_a == 3);
    REQUIRE(x2->m_b == 4);

    // using delete expression directory
    ::delete x1;

    // is equivalent to this two-step process:
    // destruction, then deallocation
    x2->~X();
    ::operator delete(addr);
}