// require1.cpp
// The many uses of 'requires'.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <concepts>
#include <type_traits>

struct Arg0 {};

struct Arg1 {
  auto call_me() -> int { return 1; }
};

struct Arg2 {
  auto call_me() noexcept -> int { return 1; }
};

template <typename T>
auto function([[maybe_unused]] T const& val) -> int {
  auto const has_member = requires(T v) {
    { v.call_me() } noexcept -> std::same_as<int>;
  };

  if constexpr (has_member) {
    return 1;
  } else {
    return 2;
  }
}

TEST_CASE("the expected template instantiation is invoked") {
  REQUIRE(function(Arg0{}) == 2);
  REQUIRE(function(Arg1{}) == 2);
  REQUIRE(function(Arg2{}) == 1);
} 