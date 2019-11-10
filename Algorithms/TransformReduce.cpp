// TransformReduce.cpp
// Demo of std::transform_reduce.
//
// NOTE: must compile with /std:c++17

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

int main()
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);

    auto res = std::transform_reduce(v.begin(), v.end(), 0,
        [](auto a, auto b){ return a + b; }, 
        [](auto a){ return a*a; }
    );

    std::cout << "Result = " << res << std::endl;
}