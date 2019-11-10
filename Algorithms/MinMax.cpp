// MinMax.cpp
// Demo of minimum / maximum algorithms.

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

int main()
{
    std::cout << "min(5, 10) = " << std::min(5, 10) << std::endl;
    std::cout << "max(5, 10) = " << std::max(5, 10) << std::endl;

    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);

    auto min = std::min_element(v.begin(), v.end());
    auto max = std::max_element(v.begin(), v.end());

    std::cout << "min element = " << *min << std::endl;
    std::cout << "max element = " << *max << std::endl;

    auto minmax = std::minmax_element(v.begin(), v.end());

    std::cout << "minmax_element = " << "(" << *minmax.first << "," << *minmax.second << ")" << std::endl;
}