// crash_course.cpp
// Dedication from C++ Crash Course.

#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>

int main()
{
    auto i{ 0x01B99644 };
    std::string x{ " DFaeeillnor" };
    while (i--)
    {
        std::next_permutation(x.begin(), x.end());
    }
    std::cout << x;

    return EXIT_SUCCESS;
}