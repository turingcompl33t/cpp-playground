// dev_null.cpp
// An iterator that just consumes its input.

#include <cstdlib>
#include <iterator>

class dev_null_iterator
{
public:
    using iterator_category = std::output_iterator_tag;

    dev_null_iterator& operator++() { return *this; }
    dev_null_iterator& operator*() { return *this; }

    template <typename T>
    dev_null_iterator& operator=(T const&)
    {
        return *this;
    } 
};

int main()
{
    return EXIT_SUCCESS;
}