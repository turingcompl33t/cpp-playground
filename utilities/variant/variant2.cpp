// variant2.cpp
// Basic usage of std::visit.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <variant>
#include <type_traits>

struct Type1 {};
struct Type2 {};
struct Type3 {};

using vary = std::variant<Type1, Type2, Type3>;

TEST_CASE("std::variant supports visitation via generic lambdas")
{
  auto v = vary{};
  auto l = [](auto const& v_) -> int {
    // must decay to discard the qualifiers we don't care about
    // (const, volatile, reference qualifiers)
    using T = std::decay_t<decltype(v_)>;

    if constexpr(std::is_same_v<T, Type1>) {
      return 0;
    } else if constexpr(std::is_same_v<T, Type2>) {
      return 1;
    } else if constexpr(std::is_same_v<T, Type3>) {
      return 2;
    } else {
      return 3;
      // static_assert(false);
    }
  };

  SECTION("First type (Type1)") {
    v.emplace<Type1>();
    REQUIRE(v.index() == 0);

    auto i = std::visit(l, v);
    REQUIRE(i == 0);
  }

  SECTION("Second type (Type2)") {
    v.emplace<Type2>();
    REQUIRE(v.index() == 1);

    auto i = std::visit(l, v);
    REQUIRE(i == 1);
  }

  SECTION("Third type (Type3)") {
    v.emplace<Type3>();
    REQUIRE(v.index() == 2);

    auto i = std::visit(l, v);
    REQUIRE(i == 2);
  }
}

struct Visitor {
  auto operator()(Type1) -> int {
    return 0;
  }

  auto operator()(Type2) -> int {
    return 1;
  }

  auto operator()(Type3) -> int {
    return 2;
  }
};

TEST_CASE("std::variant supports visition via overloaded callables")
{
  auto v = vary{};
  auto visitor = Visitor{};

  SECTION("First type (Type1)") {
    REQUIRE(v.index() == 0);

    auto i = std::visit(visitor, v);
    REQUIRE(i == 0);
  }

  SECTION("Second type (Type2)") {
    v.emplace<Type2>();

    REQUIRE(v.index() == 1);

    auto i = std::visit(visitor, v);
    REQUIRE(i == 1);
  }

  SECTION("Third type (Type3)") {
    v.emplace<Type3>();

    REQUIRE(v.index() == 2);

    auto i = std::visit(visitor, v);
    REQUIRE(i == 2);
  }
}

template <typename... Ts> 
struct overloaded {};

template <typename T, typename... Ts>
struct overloaded<T, Ts...> : T, overloaded<Ts...> {
  overloaded(T t, Ts... rest) : T{t}, overloaded<Ts...>{rest...} {}

  using T::operator();
  using overloaded<Ts...>::operator();
};

template <typename T>
struct overloaded<T> : T
{
  overloaded(T t) : T{t} {}
  using T::operator();
};

template <typename... Ts>
auto make_visitor(Ts... ts) {
  return overloaded<Ts...>(ts...);
}

TEST_CASE("std::variant supports visitation via variadic template functions") {
  auto v = vary{};

  auto visitor = make_visitor(
    [&](Type1){ return 0; },
    [&](Type2){ return 1; },
    [&](Type3){ return 2; });

  SECTION("First type (Type1)") {
    REQUIRE(v.index() == 0);

    auto i = std::visit(visitor, v);
    REQUIRE(i == 0);
  }

  SECTION("Second type (Type2)") {
    v.emplace<Type2>();

    REQUIRE(v.index() == 1);

    auto i = std::visit(visitor, v);
    REQUIRE(i == 1);
  }

  SECTION("Third type (Type3)") {
    v.emplace<Type3>();

    REQUIRE(v.index() == 2);

    auto i = std::visit(visitor, v);
    REQUIRE(i == 2);
  }
}