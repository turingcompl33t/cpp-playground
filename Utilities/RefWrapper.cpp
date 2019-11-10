// RefWrapper.cpp
// Demo of std::reference_wrapper.

#include <list>
#include <random>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>

int main()
{
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), 0);

    // initialize a vector of references to the values in the list
    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());

    std::random_device r;
    std::mt19937 g { r() };

    std::shuffle(v.begin(), v.end(), g);

    std::cout << "Original contents of list, as seen through shuffled vector: ";
    for (int& i: v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Squaring contents of original list..." << std::endl;

    std::transform(l.begin(), l.end(), l.begin(), 
        [](int i){ return i*i; }
    );

    std::cout << "New contents of list, as seen through shuffled vector: ";
    for (int& i: v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;


}