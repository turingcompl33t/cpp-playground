// bench.cpp
// Benchmarking the worst-case latency for spinlock acquire operations.
//
// Benchmark setup inspried by blog post by Malte Skarupke:
// https://probablydance.com/2019/12/30/measuring-mutexes-spinlocks-and-how-bad-the-linux-scheduler-really-is/

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include "lib/fast_spinlock.hpp"
#include "lib/naive_spinlock.hpp"
#include "lib/tatas_spinlock.hpp"
#include "lib/yielding_spinlock.hpp"

// the number of maximum latency values we print
// at the conclusion of the benchmark for each lock type
constexpr static auto const N_LATENCIES_TO_PRINT = 4;

// the number of test iterations we perform for each lock type
constexpr static auto const N_ITERS_PER_LOCK = 128ul;

// the number of loops we perform in each test iteration
constexpr static auto const N_LOOPS_PER_ITER = 16'384ul;

template <typename LockType>
static auto test_loop(LockType& lock, std::size_t const n_loops)
    -> std::chrono::milliseconds {
  using hr_clock = std::chrono::high_resolution_clock;

  auto longest_wait = std::chrono::milliseconds::zero();

  for (auto i = 0ul; i < n_loops; ++i) {
    auto const start = hr_clock::now();
    lock.acquire();
    auto const stop = hr_clock::now();

    auto const wait =
        std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    longest_wait = std::max(wait, longest_wait);

    lock.release();
  }

  return longest_wait;
}

template <typename LockType>
static auto run_one_iteration(std::size_t const n_threads)
    -> std::chrono::milliseconds {
  using ms_future = std::future<std::chrono::milliseconds>;

  auto highest_latency_for_iteration = std::chrono::milliseconds::zero();

  LockType lock{};

  std::vector<ms_future> futures{};
  for (auto i = 0ul; i < n_threads; ++i) {
    futures.emplace_back(std::async(std::launch::async, test_loop<LockType>,
                                    std::ref(lock), N_LOOPS_PER_ITER));
  }

  for (auto& fut : futures) {
    highest_latency_for_iteration =
        std::max(highest_latency_for_iteration, fut.get());
  }

  return highest_latency_for_iteration;
}

template <typename LockType>
static auto run_n_iterations(std::size_t const n_iters,
                             std::size_t const n_threads)
    -> std::vector<std::chrono::milliseconds> {
  std::vector<std::chrono::milliseconds> latencies{};
  latencies.reserve(n_iters);

  for (auto i = 0ul; i < n_iters; ++i) {
    auto const highest_latency_for_iter =
        run_one_iteration<LockType>(n_threads);
    latencies.push_back(highest_latency_for_iter);
  }

  return latencies;
}

template <typename LockType>
static auto latencies_for_lock(std::size_t const n_threads)
    -> std::vector<std::chrono::milliseconds> {
  return run_n_iterations<LockType>(N_ITERS_PER_LOCK, n_threads);
}

static auto
print_top_n_latencies(std::size_t const n,
                      std::vector<std::chrono::milliseconds>&& latencies)
    -> void {
  using diff_t = std::vector<std::chrono::milliseconds>::difference_type;

  std::partial_sort(
      std::begin(latencies), std::begin(latencies) + static_cast<diff_t>(n),
      std::end(latencies), std::greater<std::chrono::milliseconds>{});

  for (auto i = 0ul; i < n; ++i) {
    std::cout << latencies[i].count() << "ms ";
  }
  std::cout << std::endl;
}

int main() {
  // multiply hardware concurrency level by 2 to account for hyperthreading
  // (on my system)
  auto const n_threads = std::thread::hardware_concurrency() * 2;

  std::cout << "naive_spinlock:\n\t";
  print_top_n_latencies(N_LATENCIES_TO_PRINT,
                        latencies_for_lock<naive_spinlock>(n_threads));

  std::cout << "tatas_spinlock:\n\t";
  print_top_n_latencies(N_LATENCIES_TO_PRINT,
                        latencies_for_lock<tatas_spinlock>(n_threads));

  std::cout << "yielding_spinlock:\n\t";
  print_top_n_latencies(N_LATENCIES_TO_PRINT,
                        latencies_for_lock<yielding_spinlock>(n_threads));

  std::cout << "fast_spinlock:\n\t";
  print_top_n_latencies(N_LATENCIES_TO_PRINT,
                        latencies_for_lock<fast_spinlock>(n_threads));

  return EXIT_SUCCESS;
}