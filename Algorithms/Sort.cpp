// Sort.cpp
// Demo of std:sort.

#include <random>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

int main()
{
    std::vector<int> v1(10);
    std::iota(v1.begin(), v1.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(v1.begin(), v1.end(), g);

    std::cout << "Input vector: ";
    for (int i : v1)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::sort(v1.begin(), v1.end());

    std::cout << "After sort: ";
    for (int i : v1)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}