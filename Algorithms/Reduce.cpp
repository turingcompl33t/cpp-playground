// Reduce.cpp
// Demo of std::reduce.
//
// NOTE: Must compile with /std:c++17

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

// must name do_count to avoid naming collisions
template <typename I, typename T>
auto do_count(I f, I l, const T& val) -> int
{
    return std::reduce(f, l, 0, 
        [val](auto a, auto b){ return a + (b == val); });
}

int main()
{
    std::vector<int> v{2, 3, 4, 3, 4, 6, 3};

    int res = do_count(v.begin(), v.end(), 3);

    std::cout << "Number of elements that are equal to 3 is: " << res << std::endl;
}
