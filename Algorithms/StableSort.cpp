// StableSort.cpp
// Demo fo std::stable_sort.

#include <vector>
#include <algorithm>
#include <iostream>

int main()
{
    std::vector<std::string> v{ "cat", "bear", "deer", "dog", "elephant", "ox" };

    std::stable_sort(v.begin(), v.end(), 
        [](std::string const a, std::string const b) -> bool 
        { 
            return a.length() < b.length(); 
        });

    std::cout << "After stable_sort: ";
    for (std::string& s : v)
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}