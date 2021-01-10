// decltype1.cpp
// Wrapping a 'name' in parens changes the type deduced by decltype.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

static int global{0};

decltype(auto) f1() {
  return global;
}

decltype(auto) f2() {
  return (global);
}

TEST_CASE("without parens surrounding the name, the type is deduced as int") {
  global = 0;
  REQUIRE(f1() == 0);

  // does not compile: "expression must be a modifiable lvalue" (as expected)
  // f1() = 1;
}

TEST_CASE("with parens surrounding the name, the type is deduced as int&") {
  global = 0;
  REQUIRE(f2() == 0);

  f2() = 1;
  REQUIRE(global == 1);
}
