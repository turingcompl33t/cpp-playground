// ValidForType.cpp
// "Expressive TMP" from Fluent C++ blog.

#include <type_traits>
#include <iostream>

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

int main()
{
    std::cout << std::boolalpha;
    std::cout << is_incrementable<int>::value << '\n';
    std::cout << is_incrementable<std::string>::value << '\n';
    std::cout << is_decrementable<int>::value << '\n';
    std::cout << is_decrementable<std::string>::value << '\n';
}