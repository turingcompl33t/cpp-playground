// without.cpp
//
// Constructing HTML markup without builders.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 without.cpp

#include <array>
#include <string>
#include <sstream>
#include <iostream>

int main()
{
    auto words = std::array<std::string, 2>{"hello", "world"};
    
    auto oss = std::ostringstream{};

    oss << "<ul>";
    for (auto const& w : words)
    {
        oss << "<li>" << w << "</li>";
    }
    oss << "</ul>";

    auto html = oss.str().c_str();
    
    std::cout << html << std::endl;
}