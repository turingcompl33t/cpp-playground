// lockfree_shared_ptr.cpp
//
// Quick program to query the current implementation's support
// for lockfree operations on std::shared_ptr.

#include <atomic>
#include <memory>
#include <cstdlib>
#include <iostream>

struct Data
{
    unsigned a;
    unsigned b;
};

int main()
{
    auto shared_int  = std::make_shared<int>(5);
    auto shared_data = std::make_shared<Data>(); 

    if (std::atomic_is_lock_free(&shared_int))
    {
        std::cout << "std::shared_ptr<int> is lock free\n";
    }

    if (std::atomic_is_lock_free(&shared_data))
    {
        std::cout << "std::shared_ptr<Data> is lock free\n";
    }

    return EXIT_SUCCESS;
}