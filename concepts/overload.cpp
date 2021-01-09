// overload.cpp
// Using concepts + constraints to select function template overloads.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <concepts>

enum class FunctionId {
  ZERO,
  ONE,
  TWO
};

struct Arg0 {};

struct Arg1 {
  auto call0() -> void {}
};

struct Arg2 {
  auto call0() -> void {}
  auto call1() -> void {}
};

template <typename T>
concept HasCall0 = requires(T t) {
  { t.call0() };
};

template <typename T>
concept HasCall1 = requires(T t) {
  { t.call0() };
  { t.call1() };
};

template <typename T>
concept HasCall0AndCall1 = HasCall0<T> && HasCall1<T>;

// unconstrained overload
auto selector([[maybe_unused]] auto const& val) -> FunctionId {
  return FunctionId::ZERO;
}

// overload that requires just call0()
auto selector([[maybe_unused]] HasCall0 auto const& val) -> FunctionId {
  return FunctionId::ONE;
}

// overload that requires both call0() and call1()
auto selector([[maybe_unused]] HasCall0AndCall1 auto const& val) -> FunctionId {
  return FunctionId::TWO;
}

TEST_CASE("the expected overload is selected based on constraints") {
  REQUIRE(selector(Arg0{}) == FunctionId::ZERO);
  REQUIRE(selector(Arg1{}) == FunctionId::ONE);
  REQUIRE(selector(Arg2{}) == FunctionId::TWO);
}