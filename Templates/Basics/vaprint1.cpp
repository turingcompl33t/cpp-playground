// varprint1.cpp
// "hello world" of variadic templates - variadic print.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 vaprint1.cpp

#include <string>
#include <iostream>

template <typename T>
void print(T t)
{
    std::cout << t;
}

template <typename T, typename... Args>
void print(T t, Args... args)
{
    std::cout << t << ' ';
    print(args...);
}

int main()
{
    auto s = std::string{"world"};

    // double, char const*, std::string, char
    print(7.5, "hello", s, '!');
}