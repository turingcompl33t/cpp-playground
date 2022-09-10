/**
 * @file main.cpp
 * @author Kyle Dotterrer
 * @brief Demonstration of BitVector.
 * @version 0.1
 * @date 2022-09-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cstdio>
#include <cstdlib>

#include "BitVector.hpp"

#define REQUIRE(expr) assert((expr))

auto construction() -> void {
  auto v = BitVector();
  REQUIRE(v.Size() == 0);
  REQUIRE(v.Capacity() == 0);
}

auto push_back() -> void {
  auto v = BitVector();
  REQUIRE(v.Size() == 0);

  v.PushBack(true);
  REQUIRE(v.Size() == 1);

  v.PushBack(true);
  REQUIRE(v.Size() == 2);
}

auto read_values() -> void {
  auto v = BitVector();

  v.PushBack(true);
  v.PushBack(false);

  REQUIRE(v[0]);
  REQUIRE(!v[1]);
}

auto write_values() -> void {
  auto v = BitVector();

  v.PushBack(true);
  v.PushBack(true);
  REQUIRE(v[0]);
  REQUIRE(v[1]);

  v[0] = false;
  REQUIRE(!v[0]);
  REQUIRE(v[1]);
}

auto flip_values() -> void {
  auto v = BitVector();
  v.PushBack(true);
  auto const cached = static_cast<bool>(v[0]);
  v[0].flip();
  REQUIRE(v[0] != cached);
}

auto front() -> void {
  auto v = BitVector();

  v.PushBack(true);
  REQUIRE(v.Front());

  v.Front() = false;
  REQUIRE(!v.Front());
}

auto back() -> void {
  auto v = BitVector();

  v.PushBack(true);
  REQUIRE(v.Back());

  v.Back() = false;
  REQUIRE(!v.Back());
}

auto main() -> int {
  // BitVector can be constructed
  construction();
  // Values can be added
  push_back();
  // Values can be read
  read_values();
  // Values can be written
  write_values();
  // Values can be flipped
  flip_values();
  // Access to front() works
  front();
  // Access to back() works
  back();

  return EXIT_SUCCESS;
}