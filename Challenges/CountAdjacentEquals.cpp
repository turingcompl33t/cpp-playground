// CoutnAdjacentEquals.cpp
// Count the number of occurrences of adjacent equal elements in a vector.

#include <vector>
#include <numeric>
#include <functional>
#include <iostream>
#include <algorithm>

int count_adj_equals(std::vector<int>& v)
{
    return std::inner_product(v.begin(), 
        v.end(), 
        ++v.begin(), 
        0,
        std::plus<>(), 
        std::equal_to<>()
    );
}

int main()
{
    std::vector<int> v{1, 1, 2, 4, 4, 5, 9, 9, 9};

    auto res = count_adj_equals(v);

    std::cout << res << std::endl;
}