// decltype2.cpp
// We can use decltype in the body of a generic lambda to perfectly-forward arguments.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

enum class FunctionId {
  LVALUE,
  RVALUE
};

struct SomeType {};

auto function([[maybe_unused]] SomeType const& v) -> FunctionId {
  return FunctionId::LVALUE;
}

auto function([[maybe_unused]] SomeType&& v) -> FunctionId {
  return FunctionId::RVALUE;
}

TEST_CASE("decltype allows us to perform perfect-forwarding in the body of a generic lambda") {
  // the correct type is resolved in the body of 
  // the lambda thanks to reference collapsing
  auto l = [](auto&& val){
    return function(std::forward<decltype(val)>(val));
  };

  auto st = SomeType{};

  REQUIRE(l(st) == FunctionId::LVALUE);
  REQUIRE(l(SomeType{}) == FunctionId::RVALUE);
  REQUIRE(l(std::move(st)) == FunctionId::RVALUE);
}
