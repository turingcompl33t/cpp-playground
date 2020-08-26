// guard.hpp
// Simple lock guard to avoid code duplication in tests / benchmarks.

#ifndef GUARD_HPP
#define GUARD_HPP

template <typename LockType>
class guard
{
    LockType& lock;

public:
    explicit guard(LockType& lock_)
        : lock{lock_}
    {
        lock.acquire();
    }

    ~guard()
    {
        lock.release();
    }

    guard(guard const&)            = delete;
    guard& operator=(guard const&) = delete;

    guard(guard&&)            = delete;
    guard& operator=(guard&&) = delete;
};

#endif // GUARD_HPP