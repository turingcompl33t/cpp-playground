// Accumulate.cpp
// Demo of std::accumulate.

#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

int main()
{
    // initialize a new vector and fill it with 0 - 99
    std::vector<int> v( 100 );
    std::iota(v.begin(), v.end(), 0);

    auto sum = std::accumulate(v.begin(), v.end(), 0);

    std::cout << "Sum from " << *(v.begin()) << " to " << *(--v.end()) << " is: " << sum << std::endl;
}