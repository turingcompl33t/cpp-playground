// span.cpp
// Basic usage of C++20 std::span.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <span>
#include <numeric>
#include <algorithm>

constexpr static auto const SIZE = 5UL;

auto sum(std::span<int> const& span) -> int {
  return std::reduce(std::cbegin(span), std::cend(span), 0, std::plus{});
}

TEST_CASE("raw C-style array binds to std::span") {
  int array[SIZE];
  std::iota(std::begin(array), std::end(array), 0);

  auto const r = sum(array);
  REQUIRE(r == 10);
} 

TEST_CASE("std::array binds to std::span") {
  auto array = std::array<int, SIZE>{};
  std::iota(std::begin(array), std::end(array), 0);

  auto const r = sum(array);
  REQUIRE(r == 10); 
}

