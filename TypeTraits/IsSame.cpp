// IsSame.cpp

#include <iostream>
#include <type_traits>

template <typename T, typename U>
void IsSameHelper(T t, U u, std::true_type)
{
    std::cout << t << " is the same type as " << u << std::endl;
}

template <typename T, typename U>
void IsSameHelper(T t, U u, std::false_type)
{
    std::cout << t << " is not the same type as " << u << std::endl;
}

template <typename T, typename U>
void IsSame(T t, U u)
{
    IsSameHelper(t, u, typename std::is_same<T, U>::type());
}

int main()
{
    IsSame(17, 29);
    IsSame(512, 3.14);
}