// Iota.cpp
// Demo of std::iota.

#include <vector>
#include <numeric>
#include <iostream>

int main()
{
    std::vector<int> v1(10);
    std::vector<int> v2(10);

    std::iota(v1.begin(), v1.end(), 0);
    std::iota(v2.begin(), v2.end(), -5);

    std::cout << "Vector 1: ";
    for (int i : v1)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Vector 2: ";
    for (int i : v2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}