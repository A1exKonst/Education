// Problem 02.09
/*
Implement algorithms for calculating the greatest common divisor (gcd)
        of two natural numbers of type int using both recursive and iterative
approaches, as well as an algorithm for calculating the least common multiple
(lcm) of two natural numbers of type int. Use the standard functions std::gcd
and std::lcm to validate the results.
*/

#include <cassert>
#include <iostream>
#include <numeric>
#include <print>
#include <stdexcept>

auto gcd_recursive(unsigned int a, unsigned int b) -> unsigned int;

auto gcd_iterative(unsigned int a, unsigned int b) -> unsigned int;

auto lcm_custom(unsigned int a, unsigned int b) -> unsigned int;

auto gcd_recursive(unsigned int a, unsigned int b) -> unsigned int {
  return b == 0 ? a : gcd_recursive(b, a % b);
}

auto gcd_iterative(unsigned int a, unsigned int b) -> unsigned int {
  while (b != 0) {
    unsigned int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// There exists mathematical equation: lcm(a, b) = (a * b) / gcd(a, b)
auto lcm_custom(unsigned int a, unsigned int b) -> unsigned int {
  if (a == 0 || b == 0)
    return 0;
  return (a / gcd_iterative(a, b)) * b; // divide first to avoid overflow
}

auto main() -> int {

  // init tests:
  std::array<std::pair<unsigned int, unsigned int>, 7> test_cases = {
      {{0, 3}, {12, 18}, {45, 10}, {7, 13}, {100, 25}, {1, 50}, {24, 60}}};

  // validate tests through std::gcd, std::lcm:
  for (const auto &[a, b] : test_cases) {

    unsigned int gcd_rec = gcd_recursive(a, b);
    unsigned int gcd_iter = gcd_iterative(a, b);
    unsigned int lcm = lcm_custom(a, b);

    unsigned int gcd_std = std::gcd(a, b);
    unsigned int lcm_std = std::lcm(a, b);

    assert(gcd_rec == gcd_std);
    assert(gcd_iter == gcd_std);
    assert(lcm == lcm_std);
  }

  std::print("[  PASSED  ]\n");
  return 0;
}
