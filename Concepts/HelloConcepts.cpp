// HelloConcepts.cpp
// Test of concept support in MSVC.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++latest HelloConcepts.cpp

#include <iostream>
#include <type_traits>

template <typename T>
concept floating_point = std::is_floating_point_v<T>;

template <typename T>
T original_syntax(T a, T b) requires floating_point<T>
{
    return a + b;
}

template <floating_point T>
T improved_syntax(T a, T b)
{
    return a + b;
}

// terse syntax currently unsupported
// T terse_syntax(floating_point auto a, floating_point auto b)
// {
//     return a + b;
// }

int main()
{
    std::cout << "Hello, Concepts!\n";
    
    auto res1 = original_syntax(1.2, 3.4);
    auto res2 = improved_syntax(1.2, 3.4);

    std::cout << res1 << '\n';
    std::cout << res2 << '\n';
}