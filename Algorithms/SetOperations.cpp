// SetOperations.cpp
// Demo of set operations.

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

template <typename T>
void print_vec(std::vector<T> const v)
{
    std::cout << "Contents: ";
    for (T e : v)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v1(10);
    std::vector<int> v2(10);
    std::vector<int> res1{};
    std::vector<int> res2{};

    std::iota(v1.begin(), v1.end(), 0);
    std::iota(v2.begin(), v2.end(), -5);

    std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(res1));

    print_vec(v1);
    print_vec(v2);

    std::cout << "number of elements in union is: " << res1.size() << std::endl;
    print_vec(res1);

    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(res2));

    std::cout << "number of elements in intersection is: " << res2.size() << std::endl;
    print_vec(res2);
}