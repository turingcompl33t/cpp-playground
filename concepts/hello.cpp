// hello.cpp
// Concepts "Hello World" with g++ 10.2.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <concepts>

template <typename T>
concept Integer = std::same_as<T, int>;

template <Integer T>
auto add_one_to_int(T const val) -> T {
  return val + 1;
} 

TEST_CASE("concepts can be used to constrain function template argument types") {
  auto const two = add_one_to_int(1);
  REQUIRE(two == 2);

  // does not compile
  // auto const fail = add_one_to_int(1U);
  // REQUIRE(fail == 2);

  // does not compile
  // auto const fail = add_one_to_int(1.0F);
  // REQUIRE(fail == 2);
}