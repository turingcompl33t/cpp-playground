// Optional.cpp
// Demo of std::optional.
//
// NOTE: must compile with: /std:c++17

#include <string>
#include <functional>
#include <optional>
#include <iostream>

auto create(bool flag)
{
    const std::string value = "Hello Optional";
    return flag ? 
        std::optional<std::string>{ value } 
        : std::nullopt;
}

int main()
{
    std::cout << "create(true).value_or('Hello Nullopt') returned: " << create(true).value_or("Hello Nullopt") << std::endl;
    std::cout << "create(false).value_or('Hello Nullopt') returned: " << create(false).value_or("Hello Nullopt") << std::endl;
}