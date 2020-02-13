// ScopedLock.cpp
// Demonstration of basic std::scoped_lock functionality.
//
// Build:
//  cl /EHsc /nologo /W4 /std:c++17 ScopedLock.cpp

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

    // acquire both locks atomically and guard release
    // here we rely on some dope template argument deduction;
    // this is equivalent to:
    // std::scoped_lock<std::mutex, std::mutex> ...
    std::scoped_lock lock{lhs.mutex_, rhs.mutex_};

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