// optional.cpp
// Basic usage of std::optional.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <optional>
#include <vector>

struct TheObject {
  explicit TheObject(int const p)
      : property_{p} {}
  int const property_;
};

enum class Selector { YES, NO };

[[nodiscard]] std::optional<TheObject> make_object(Selector select) {
  return select == Selector::YES ? std::make_optional(TheObject{16})
                                 : std::nullopt;
}

TEST_CASE("std::optional contains types") {
  auto object_opt = make_object(Selector::YES);
  if (object_opt) {
    REQUIRE(object_opt->property_ == 16);
    auto& object = object_opt.value();
    REQUIRE(object.property_ == 16);
  } else {
    FAIL("optional value evaluated to false");
  }
}

TEST_CASE("std::optional::has_value() can be used to explicitly check for presence of object") {
  auto object_opt = make_object(Selector::YES);
  if (object_opt.has_value()) {
    REQUIRE(object_opt->property_ == 16);
    auto& object = object_opt.value();
    REQUIRE(object.property_ == 16);
  } else {
    FAIL("optional value evaluated to false");
  }
}

TEST_CASE("std::optional can be empty") {
  auto object_opt = make_object(Selector::NO);
  if (object_opt) {
    FAIL("the object is not empty");
  }
  REQUIRE_FALSE(object_opt.has_value());
}

TEST_CASE("std::optional supports convenience method value_or()") {
  auto object_yes = make_object(Selector::YES);
  auto object_no = make_object(Selector::NO);

  auto opt_yes = object_yes.value_or(TheObject{18});
  auto opt_no = object_no.value_or(TheObject{18});

  REQUIRE(opt_yes.property_ == 16);
  REQUIRE(opt_no.property_ == 18);
}

TEST_CASE("std::optional supports in-place construction of wrapped object") {
  // the std::string will only ever be constructed 'within' the optional
  std::optional<std::string> opt1{std::in_place, "hello"};

  REQUIRE(opt1.has_value());
  REQUIRE(opt1.value() == std::string{"hello"});
}

TEST_CASE("std::optional throws on invalid access to optional object") {
  std::optional<std::string> opt{};
  REQUIRE_THROWS_AS(opt.value(), std::bad_optional_access);
}

// NOTE: disgusting
inline std::size_t dtor_call_count{0};
struct SomeType {
  SomeType() {}
  ~SomeType() {
    ++dtor_call_count;
  }
};

TEST_CASE("std::optional::reset() can be used to destroy the wrapped object") {
  dtor_call_count = 0;
  
  std::optional<SomeType> opt{std::in_place};
  REQUIRE(dtor_call_count == 0);

  opt.reset();
  REQUIRE(dtor_call_count == 1);
}

TEST_CASE("std::optional::swap() can be used to exchange the contents of the optional") {
  std::optional<SomeType> opt1{std::in_place};
  std::optional<SomeType> opt2{};

  REQUIRE(opt1.has_value());
  REQUIRE_FALSE(opt2.has_value());

  opt1.swap(opt2);

  REQUIRE_FALSE(opt1.has_value());
  REQUIRE(opt2.has_value());
}