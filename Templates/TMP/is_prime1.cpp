// is_prime1.cpp
// Basic compile time computation with C++98 features.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I C:\Dev\Catch2 is_prime1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

template <unsigned p, unsigned d>
struct is_prime_impl
{
    static constexpr bool value = (p%d != 0) && is_prime_impl<p,d-1>::value;
};

template <unsigned p>
struct is_prime_impl<p,2>
{
    static constexpr bool value = (p%2 != 0);
};

template <unsigned p>
struct is_prime
{
    static constexpr bool value = is_prime_impl<p,p/2>::value;
};

template <>
struct is_prime<0> { static constexpr bool value = false; };
template <>
struct is_prime<1> { static constexpr bool value = false; };
template <>
struct is_prime<2> { static constexpr bool value = true; };
template <>
struct is_prime<3> { static constexpr bool value = true; };

TEST_CASE("is_prime computes primality at compile time")
{
    REQUIRE(is_prime<7>::value);
    REQUIRE_FALSE(is_prime<9>::value);
}