// SumSquaresThrough.cpp
// Demo of basic range usage: calculating the sum of 
// squares up through a specified maximum value.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++latest /permissive- /experimental:preprocessor /I C:\Dev\Rangev3\Include SumSquaresThrough.cpp

#include <iostream>
#include <range/v3/all.hpp>

int sum_squares_through(int max)
{
    auto r_int = ranges::iota(1);
    auto rng = r_int | ranges::views::transform([](int i){return i*i;});
    return ranges::accumulate(rng | ranges::views::take(max), 0);
}

int main()
{   
    auto s1 = sum_squares_through(3);
    auto s2 = sum_squares_through(9);

    std::cout << s1 << '\n';
    std::cout << s2 << '\n';
}