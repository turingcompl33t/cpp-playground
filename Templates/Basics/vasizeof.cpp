// vasizeof.cpp
// Using the "new" sizeof... operator to determine size of
// template paramter and function parameter packs
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 vasizeof.cpp

#include <iostream>

template <typename T>
void unpack(T)
{
    std::cout << "0 type parameters in pack; ";
    std::cout << "0 function parameters in pack\n";
}

template <typename T, typename... Ts>
void unpack(T, Ts... ts)
{
    std::cout << sizeof...(Ts) << " type parameters in pack; ";
    std::cout << sizeof...(ts) << " function parameters in pack\n";
    unpack(ts...);
}

int main()
{
    unpack(1, 2, 3, 4);
}