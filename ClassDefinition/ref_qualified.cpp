// ref_qualified.cpp

#include <tuple>
#include <cstdlib>
#include <iostream>

class SomeObject
{
    std::size_t lvalue_count;
    std::size_t rvalue_count;

public:
    SomeObject() 
        : lvalue_count{0}
        , rvalue_count{0}
    {}

    void SomeMethod() & { lvalue_count++; }
    void SomeMethod() && { rvalue_count++; }

    std::pair<std::size_t, std::size_t> GetCounts() const noexcept
    {
        return std::make_pair(lvalue_count, rvalue_count);
    }
};

int main()
{
    return EXIT_SUCCESS;
}