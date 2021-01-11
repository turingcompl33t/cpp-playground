// yielding_spinlock.hpp
// A spinlock that tracks its spin count internally and
// yields to the operating system in the events that the
// spin count exceeds some threshold.

#ifndef YIELDING_SPINLOCK_HPP
#define YIELDING_SPINLOCK_HPP

#include <atomic>
#include <emmintrin.h>
#include <thread>

class yielding_spinlock {
  constexpr static std::size_t const DEFAULT_SPIN_COUNT = 16;

  std::atomic<bool> locked;
  std::size_t const spin_count;

public:
  constexpr yielding_spinlock()
      : yielding_spinlock{DEFAULT_SPIN_COUNT} {}

  explicit constexpr yielding_spinlock(std::size_t const spin_count_)
      : locked{false}
      , spin_count{spin_count_} {}

  yielding_spinlock(yielding_spinlock const&) = delete;
  yielding_spinlock& operator=(yielding_spinlock const&) = delete;

  yielding_spinlock(yielding_spinlock&&) = delete;
  yielding_spinlock& operator=(yielding_spinlock&&) = delete;

  auto acquire() -> void {
    for (std::size_t local_spin_count = 0; !try_acquire(); ++local_spin_count) {
      if (local_spin_count < spin_count) {
        _mm_pause();
      } else {
        std::this_thread::yield();
        local_spin_count = 0;
      }
    }
  }

  auto release() -> void { locked.store(false, std::memory_order_release); }

private:
  auto try_acquire() -> bool {
    return (!locked.load(std::memory_order_acquire) &&
            !locked.exchange(true, std::memory_order_acquire));
  }
};

#endif  // YIELDING_SPINLOCK_HPP