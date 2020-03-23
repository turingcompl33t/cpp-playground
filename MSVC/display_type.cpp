// dsiplay_type.cpp
// 
// Demo of MSVC's /d1reportSingleClassLayout option.
//
// cl /EHsc /nologo /std:c++17 /W4 /d1reportSingleClassLayoutXVector dsiplay_type.cpp

#include <vector>
#include <iostream>

struct XVector : public std::vector<int>
{
    // nothing
};

int main()
{
    std::cout << "Hello /d1reportSingleCLassLayout\n";
}