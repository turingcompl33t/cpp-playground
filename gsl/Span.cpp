// span.cpp
// Demonstration of basic GSL span<> usage.
//
// Build:
//  cl /EHsc /nologo /W4 /std:c++17 /I C:\Dev\GSL\include Span.cpp

#include <vector>
#include <iterator>
#include <iostream>
#include <numeric>

#include <gsl/gsl>

void process_span(gsl::span<int> s)
{
    for (auto&i : s)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int main()
{
    int a[10];  
    std::iota(std::begin(a), std::end(a), 0);

    std::vector<int> v(10);
    std::iota(std::begin(v), std::end(v), 0);

    process_span(a);
    process_span(v);
}