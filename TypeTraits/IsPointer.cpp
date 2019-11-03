// IsPointer.cpp

#include <iostream>

template <typename T>
struct IsPointer
{
    static constexpr bool value {false};
};

template <typename T>
struct IsPointer<T*>
{
    static constexpr bool value {true};
};

int main()
{
    std::cout << "int is a pointer type:   " << IsPointer<int>::value << std::endl;
    std::cout << "void* is a pointer type: " << IsPointer<void*>::value << std::endl;
}