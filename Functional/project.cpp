// project.cpp
//
// Implementation of a "projection idiom" that generalizes 
// the concept of applying a function to every element in a container.
//
// From FluentC++ Article:
//  Various Ways of Applying a Function to the Elements of a Collection in C++
//  (https://www.fluentcpp.com/2020/02/07/transform-adaptor-equivalent-in-cpp/)
//
// Build
//  cl /EHsc /nologo /std:c++14 /W4 /I C:\Dev\Catch2 project.cpp
//
// NOTE: std::result_of_t is deprecated in C++17 in favor of
// std::invoke_result_t, but when I replace std::result_of_t with
// std::invoke_result_t and compile under C++17, the build breaks

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cmath>
#include <vector>
#include <numeric>
#include <iostream>
#include <type_traits>

struct Point
{
    double x;
    double y;
};

double norm(Point const& point)
{
    return std::sqrt(point.x * point.x + point.y * point.y);
}

template <typename Function>
auto project(Function fn)
{
    return [fn](auto const& inputs)
    {
        // deduce the value type of container elements
        using value_type = decltype(inputs.front());

        // deduce the result type which will be stored in the
        // results vector - result of applying function to element
        using fn_return_type = std::result_of_t<Function(value_type)>;

        // construct vector of results
        // use std::decay_t to strip references from deduced type
        auto results = std::vector<std::decay_t<fn_return_type>>{}; 
        results.reserve(inputs.size());

        // compute the results
        for (auto const& e : inputs)
        {
            results.push_back(std::invoke(fn, e));
        }

        return results;
    };
}

TEST_CASE("project() projects function application onto container")
{
    auto const points = std::vector<Point>{ {3,4}, {6,8}, {9,12} };

    // project the norm() function onto a container;
    // returns a function object (lambda) 
    auto compute_norms = project(norm);

    auto norms = compute_norms(points);

    REQUIRE(norms.size() == 3);

    REQUIRE(norms[0] == norm(points[0]));
    REQUIRE(norms[1] == norm(points[1]));
    REQUIRE(norms[2] == norm(points[2]));
}