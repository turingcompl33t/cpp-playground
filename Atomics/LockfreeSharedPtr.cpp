// LockfreeSharedPtr.cpp
// Quick program to query the current implementation's support
// for lockfree operations on std::shared_ptr.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 LockfreeSharedPtr.cpp

#include <atomic>
#include <memory>
#include <iostream>

struct data_t
{
    unsigned a;
    unsigned b;
};

int main()
{
    auto shared_int = std::make_shared<int>(5);
    auto shared_data = std::make_shared<data_t>(); 

    if (std::atomic_is_lock_free(&shared_int))
    {
        std::cout << "std::shared_ptr<int> is lock free\n";
    }

    if (std::atomic_is_lock_free(&shared_data))
    {
        std::cout << "std::shared_ptr<data_t> is lock free\n";
    }
}