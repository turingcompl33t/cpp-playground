// bench_throughput.cpp
// Benchmarking throughput for reader-writer lock implementations.

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "lock_helpers.hpp"

// the volume of work performed under the lock;
// shared by both reader and writer tasks
constexpr static auto const WORK_LOOP = 100UL;

// the number of lock acquire operations performed by each worker
constexpr static auto const REPS_PER_WORKER = 1000UL;

constexpr static auto const ITERS_PER_CONFIG = 100UL;

// proportion of writer workers
constexpr static std::array PROPS{0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

constexpr static auto const MIN_WORKERS = 2UL;
constexpr static auto const MAX_WORKERS = 64UL;

using duration_t = std::chrono::milliseconds;

auto work() -> void {
  for (auto i = 0UL; i < WORK_LOOP; ++i) {
    ;
  }
}

template <typename LockType> auto writer(LockType& lock, Latch& latch) -> void {
  latch.arrive_and_wait();
  for (auto i = 0UL; i < REPS_PER_WORKER; ++i) {
    WriteGuard<LockType> guard{lock};
    work();
  }
}

template <typename LockType> auto reader(LockType& lock, Latch& latch) -> void {
  latch.arrive_and_wait();
  for (auto i = 0UL; i < REPS_PER_WORKER; ++i) {
    ReadGuard<LockType> guard{lock};
    work();
  }
}

template <typename LockType>
auto run_one_iteration(std::size_t const n_writers, std::size_t const n_readers)
    -> duration_t::rep {
  using clock = std::chrono::high_resolution_clock;

  auto const total_workers = n_writers + n_readers;

  Latch latch{total_workers + 1};
  LockType lock{};

  std::vector<std::thread> workers{};
  workers.reserve(total_workers);

  for (auto _ = 0UL; _ < n_writers; ++_) {
    workers.emplace_back(writer<LockType>, std::ref(lock), std::ref(latch));
  }
  for (auto _ = 0UL; _ < n_readers; ++_) {
    workers.emplace_back(reader<LockType>, std::ref(lock), std::ref(latch));
  }

  auto const start = clock::now();
  latch.arrive_and_wait();
  for (auto& w : workers) {
    w.join();
  }
  auto const stop = clock::now();
  auto const time = std::chrono::duration_cast<duration_t>(stop - start);
  return time.count();
}

template <typename LockType> auto bench_throughput() -> void {
  for (auto n_workers = MIN_WORKERS; n_workers <= MAX_WORKERS;
       n_workers <<= 1) {
    for (const auto prop : PROPS) {
      auto const n_writers = std::max(
          static_cast<std::size_t>(static_cast<double>(n_workers) * prop), 1UL);
      auto const n_readers =
          std::max(static_cast<std::size_t>(static_cast<double>(n_workers) *
                                            (1.0 - prop)),
                   1UL);

      std::vector<duration_t::rep> durations{};
      durations.reserve(ITERS_PER_CONFIG);
      for (auto _ = 0UL; _ < ITERS_PER_CONFIG; ++_) {
        auto const duration = run_one_iteration<LockType>(n_writers, n_readers);
        durations.push_back(duration);
      }

      auto const avg = std::accumulate(durations.cbegin(), durations.cend(),
                                       duration_t::rep{}) /
                       static_cast<duration_t::rep>(ITERS_PER_CONFIG);
      std::cout << "N_WORKERS: " << n_workers << " PROP: " << prop
                << " DURATION: " << avg << "ms" << std::endl;
    }
  }
}

auto main() -> int {
  bench_throughput<std::shared_mutex>();
  bench_throughput<tbb::reader_writer_lock>();
  return EXIT_SUCCESS;
}