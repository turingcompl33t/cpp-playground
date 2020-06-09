// optional_valueor.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 optional_valueor.cpp

#include <string>
#include <optional>
#include <iostream>
#include <functional>

auto create(bool flag)
{
    std::string const value = "Hello Optional";
    return flag ? 
        std::optional<std::string>{ value } 
        : std::nullopt;
}

int main()
{
    std::cout << "create(true).value_or('Hello Nullopt') returned: ";
    std::cout << create(true).value_or("Hello Nullopt") << '\n';
    std::cout << "create(false).value_or('Hello Nullopt') returned: "; 
    std::cout << create(false).value_or("Hello Nullopt") << '\n';
}