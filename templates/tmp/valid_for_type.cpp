// valid_for_type.cpp
// "Expressive TMP" from Fluent C++ blog.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I %CPP_WORKSPACE%\_Deps\Catch2 valid_for_type.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <type_traits>

template <typename ...>
using try_to_instantiate = void;

template <typename T, template <typename> class Expression, typename Attempt = void>
struct is_detected : std::false_type {};

template <typename T, template <typename> class Expression>
struct is_detected<T, Expression, try_to_instantiate<Expression<T>>> : std::true_type {};

template <typename T>
using increment_expression = decltype(++std::declval<T&>());

template <typename T>
using is_incrementable = is_detected<T, increment_expression>;

template <typename T>
using decrement_expression = decltype(--std::declval<T&>());

template <typename T>
using is_decrementable = is_detected<T, decrement_expression>;

TEST_CASE("type properties are determined at compile time")
{
    REQUIRE(is_incrementable<int>::value);
    REQUIRE_FALSE(is_incrementable<std::string>::value);

    REQUIRE(is_decrementable<int>::value);
    REQUIRE_FALSE(is_decrementable<std::string>::value);
}