// ForwardIterator.cpp
// Demo of basic forward iterator usage.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 ForwardIterator.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <forward_list>

TEST_CASE("std::forward_list begin() and end() provide forward iterators")
{
    int double_sum{};
    std::forward_list<int> fl{1, 2, 3};

    auto iter1 = fl.begin();
    auto iter2 = iter1;  // copy assign iter2 from iter1

    while (iter1 != fl.end())
        double_sum += *(iter1++);

    REQUIRE(double_sum == 6);

    while (iter2 != fl.end())
        double_sum += *(iter2++);

    REQUIRE(double_sum == 12);
}