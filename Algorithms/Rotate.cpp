// Rotate.cpp
// Demo of std::rotate.

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);

    std::cout << "Before: ";
    for (int i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::rotate(v.begin(), v.begin() + 4, v.end());

    std::cout << "After: ";
    for (int i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}