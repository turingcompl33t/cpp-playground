// Convenience.cpp
// Demo of basic range utility: convenience.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++latest /permissive- /experimental:preprocessor /I C:\Dev\Rangev3\Include Convenience.cpp

#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <range/v3/all.hpp>

int main()
{
    std::vector<int> v1{3, 2, 1};
    std::sort(v1.begin(), v1.end());
    std::for_each(v1.begin(), v1.end(), [&](int i){std::cout << i << ' ';});

    std::cout << '\n';

    std::vector<int> v2{3, 2, 1};
    ranges::sort(v2);
    std::for_each(v2.begin(), v2.end(), [&](int i){std::cout << i << ' ';});
}