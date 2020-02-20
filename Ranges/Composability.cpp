// Composability.cpp
// Demo of basic range utility: composability.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++latest /permissive- /experimental:preprocessor /I C:\Dev\Rangev3\Include Composability.cpp

#include <vector>
#include <numeric>
#include <iostream>
#include <range/v3/all.hpp>

using namespace ranges;

int main()
{
    auto v = std::vector<int>(10);
    std::iota(v.begin(), v.end(), 0);

    std::cout << "Original Contents:\n";
    std::for_each(v.begin(), v.end(), [&](int i){std::cout << i << ' ';});
    std::cout << '\n';

    // filter out odd values,
    // filter out values less than 4,
    // and square remaining values
    auto r = v | views::remove_if([](int i){ return i % 2 != 0; })
               | views::remove_if([](int i){ return i < 4; })
               | views::transform([](int i){ return i*2; });    

    std::cout << "After View Application:\n";
    ranges::for_each(r, [&](int i){std::cout << i << ' ';});
}