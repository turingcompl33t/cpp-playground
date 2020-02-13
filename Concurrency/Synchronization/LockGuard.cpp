// LockGuard.cpp
// Demonstration of basic std::lock_guard functionality.
//
// Build:
//  cl /EHsc /nologo /W4 /std:c++17 LockGuard.cpp

#include <mutex>
#include <thread>
#include <iostream>

struct X
{
    X(const unsigned long data)
    : data_{data}
    {}

    unsigned long data_;
    std::mutex mutex_;
};

std::ostream& operator<<(std::ostream& stream, const X& x)
{
    stream << x.data_;
    return stream;
}

void swap(X& lhs, X& rhs)
{
    if (&lhs == &rhs)
    {
        return;
    }

    // acquire both locks atomically
    std::lock(lhs.mutex_, rhs.mutex_);

    // construct a lock guard which merely adopts the already-held locks
    // here we rely on some dope template argument deduction;
    // this is equivalent to std::lock_guard<std::mutex>
    std::lock_guard guard_a{lhs.mutex_, std::adopt_lock};
    std::lock_guard guard_b{rhs.mutex_, std::adopt_lock};

    std::swap(lhs.data_, rhs.data_);
}

int main()
{
    X x0{0};
    X x1{1};

    std::cout << "Before Swap:\n";
    std::cout << "x0 = " << x0 << '\n';
    std::cout << "x1 = " << x1 << '\n';

    swap(x0, x1);

    std::cout << "After Swap:\n";
    std::cout << "x0 = " << x0 << '\n';
    std::cout << "x1 = " << x1 << '\n';
}