// DiplayTypes.cpp
// Demo of MSVC's /d1reportSingleClassLayout option.
//
// cl.exe ... /d1reportSingleClassLayoutXVector DisplayType.cpp

#include <iostream>
#include <vector>

struct XVector : public std::vector<int>
{
    // nothing
};

int main()
{
    std::cout << "Hello MSVC" << std::endl;
}