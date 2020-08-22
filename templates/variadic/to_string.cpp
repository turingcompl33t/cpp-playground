// to_string.cpp
// Demo of basic variadic template usage to convert arbitrary types
// (assuming they support input operator<<) to strings.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 to_string.cpp

#include <vector>
#include <sstream>
#include <iostream>

template <typename P1, typename ... Param>
std::vector<std::string> to_string(const P1& p1, const Param& ... param)
{
    std::vector<std::string> s;
    s.push_back(to_string_impl(p1));

    const auto remainder = to_string(param...);
    s.insert(s.end(), remainder.begin(), remainder.end());
    
    return s;
}

template <typename T>
std::string to_string_impl(const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

std::vector<std::string> to_string()
{
    return {};
}

int main()
{
    const auto vec = to_string("hello", 5, 3.0);

    for (std::string s : vec)
    {
        std::cout << s << '\n';
    }
}