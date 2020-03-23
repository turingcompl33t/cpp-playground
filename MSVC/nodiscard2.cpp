// nodiscard2.cpp
//
// cl /EHsc /nologo /std:c++17 /W4 nodiscard2.cpp

#include <iostream>

[[nodiscard("result of add_two should not be discarded!")]]
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