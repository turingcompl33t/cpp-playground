// Transform.cpp
// Demo of std::transform.

#include <numeric>
#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> v1(10);
    std::vector<int> v2(10);

    std::iota(v1.begin(), v1.end(), 0);

    std::transform(v1.begin(), v1.end(), v2.begin(), 
        [](int const i) -> int { return i*i; });

    std::cout << "Input vector: ";
    for (int i : v1)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "After transform: ";
    for (int i : v2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}