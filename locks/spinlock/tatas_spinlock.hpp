// tatas_spinlock.hpp
// A spinlock that avoids unnecessary cache invalidation
// using the test-and-test-and-set pattern.

#ifndef TATAS_SPINLOCK_HPP
#define TATAS_SPINLOCK_HPP

#include <atomic>
#include <emmintrin.h>

class tatas_spinlock
{
    std::atomic<bool> locked;

public:
    constexpr tatas_spinlock()
        : locked{false} {}

    ~tatas_spinlock() = default;

    tatas_spinlock(tatas_spinlock const&)            = delete;
    tatas_spinlock& operator=(tatas_spinlock const&) = delete;

    tatas_spinlock(tatas_spinlock&&)            = delete;
    tatas_spinlock& operator=(tatas_spinlock&&) = delete;

    void acquire()
    {
        for (;;)
        {
            auto was_locked = locked.load(std::memory_order_acquire);
            if (!was_locked 
                && locked.compare_exchange_weak(was_locked, true, std::memory_order_acquire))
            {
                break;
            }

            _mm_pause();
        }
    }

    void release()
    {
        locked.store(false, std::memory_order_release);
    }
};

#endif // TATAS_SPINLOCK_HPP