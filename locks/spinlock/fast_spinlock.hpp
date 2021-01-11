// fast_spinlock.hpp
// A yielding spinlock with performance enhancements
// built on platform-specific features.
//
// From the HPX spinlock backend, as presented by Bryce Adelstein-Lelbach
// in his CppCon 2019 Talk: "The C++20 Synchronization Library"

#ifndef FAST_SPINLOCK_HPP
#define FAST_SPINLOCK_HPP

#include <atomic>
#include <sched.h>
#include <time.h>

class fast_spinlock {
  mutable std::atomic_flag flag{ATOMIC_FLAG_INIT};

public:
  fast_spinlock() = default;
  ~fast_spinlock() = default;

  fast_spinlock(fast_spinlock const&) = delete;
  fast_spinlock& operator=(fast_spinlock const&) = delete;

  fast_spinlock(fast_spinlock&&) = delete;
  fast_spinlock& operator=(fast_spinlock&&) = delete;

  auto acquire() const -> void {
    for (auto k = 0UL; flag.test_and_set(std::memory_order_acquire); ++k) {
      if (k < 4) {
        ;
      } else if (k < 16) {
        __asm__ __volatile__("rep; nop" : : : "memory");
      } else if (k < 64) {
        // NOTE: is this differect from std::this_thread::yield()?
        // pretty sure that on Linux, this is the same under the hood
        sched_yield();
      } else {
        // NOTE: why not just use the std::chrono library?
        timespec rqtp = {0, 0};
        rqtp.tv_sec = 0;
        rqtp.tv_nsec = 1000;
        nanosleep(&rqtp, nullptr);
      }
    }
  }

  auto release() const -> void { flag.clear(std::memory_order_release); }
};

#endif  // FAST_SPINLOCK_HPP