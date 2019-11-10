// Partition.cpp
// Demo of std::partition.

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> v1(10);
    std::vector<int> v2(10);

    std::iota(v1.begin(), v1.end(), 0);
    std::iota(v2.begin(), v2.end(), 0);

    auto pred = [](int const i){ return i % 2 == 0; };

    std::partition(v1.begin(), v1.end(), pred);

    std::cout << "Original Vector: ";
    for (int i : v2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Partitioned Vector: ";
    for (int i : v1)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    auto b_part = std::is_partitioned(v1.begin(), v1.end(), pred);
    auto b_orig = std::is_partitioned(v2.begin(), v2.end(), pred);

    std::cout << "Is original paritioned? " << b_orig << std::endl;
    std::cout << "Is new version partitioned? " << b_part << std::endl; 
}