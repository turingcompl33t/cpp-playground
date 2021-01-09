// forwarding1.cpp
// Perfect forwarding.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <utility>

enum class FunctionId {
  LVALUE,
  RVALUE
};

struct SomeType {};

auto overload([[maybe_unused]] SomeType& val) -> FunctionId {
  return FunctionId::LVALUE;
}

auto overload([[maybe_unused]] SomeType&& val) -> FunctionId {
  return FunctionId::RVALUE;
}

template<typename T>
auto just_forward(T&& val) -> FunctionId {
  return overload(std::forward<T>(val));
}

TEST_CASE("the expected overload is selected with an prvalue(?)") {
  REQUIRE(just_forward(SomeType{}) == FunctionId::RVALUE);
}

TEST_CASE("the expected overload is selected with an xvalue(?)") {
  auto v = SomeType{};
  REQUIRE(just_forward(std::move(v)) == FunctionId::RVALUE);
}

TEST_CASE("the expected overload is selected with an lvalue") {
  auto v = SomeType{};
  REQUIRE(just_forward(v) == FunctionId::LVALUE);
}