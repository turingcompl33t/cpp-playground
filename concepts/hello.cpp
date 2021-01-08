// hello.cpp
// Concepts "Hello World" with g++ 10.2.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cstdlib>
#include <concepts>

template <typename T>
concept Integer = std::same_as<T, int>;

template <typename T>
auto add_one_to_int(T const val) -> T {
  return val + 1;
} 

TEST_CASE("it works") {
  auto const two = add_one_to_int(1);
  REQUIRE(two == 2);
}