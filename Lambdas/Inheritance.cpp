// Inheritance.cpp
// Inheriting from a lambda.
//
// NOTE: must compile with /std:c++17

#include <iostream>

template <typename T, typename U>
struct Test : T, U
{
    Test(T t, U u) :
        T(std::move(t)), U(std::move(u)) {}
    using T::operator();
    using U::operator();
};

int main()
{
    auto f1 = [](){ std::cout << "Hello from Lambda 1" << std::endl; };
    auto f2 = [](int i){ std::cout << "Hello from Lambda 2" << std::endl; };

    auto combo = Test(f1, f2);

    combo();
    combo(5);
}