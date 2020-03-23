// nodiscard1.cpp
//
// cl /EHsc /nologo /std:c++17 /W4 nodiscard1.cpp

#include <iostream>

[[nodiscard]]
int add_two(int v)
{
    return v + 2;
}

int main()
{
    std::cout << "Hello [[nodiscard]]\n";
    
    // C4834
    // add_two(1);

    // fine
    auto res = add_two(1);

    return res;
}