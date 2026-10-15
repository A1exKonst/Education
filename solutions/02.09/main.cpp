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

int gcd_recursive(int a, int b);

int gcd_iterative(int a, int b);

int lcm_custom(int a, int b);

int gcd_recursive(int a, int b) {
  if (a < 0 || b < 0) {
    throw std::invalid_argument("gcd expects positive numbers.");
  }
  return b == 0 ? a : gcd_recursive(b, a % b);
}

int gcd_iterative(int a, int b) {
  if (a < 0 || b < 0) {
    throw std::invalid_argument("gcd expects positive numbers.");
  }
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// There exists mathematical equation: lcm(a, b) = (a * b) / gcd(a, b)
int lcm_custom(int a, int b) {
  if (a < 0 || b < 0) {
    throw std::invalid_argument(
        "Числа должны быть натуральными (положительными).");
  }
  if (a == 0 || b == 0)
    return 0;
  return (a / gcd_iterative(a, b)) * b;
}

int main() {

  // init tests:
  std::pair<int, int> test_cases[] = {{0, 3},    {12, 18}, {45, 10}, {7, 13},
                                      {100, 25}, {1, 50},  {24, 60}};

  // validate tests through std::gcd, std::lcm:
  for (const auto &[a, b] : test_cases) {

    int gcd_rec = gcd_recursive(a, b);
    int gcd_iter = gcd_iterative(a, b);
    int lcm = lcm_custom(a, b);

    int gcd_std = std::gcd(a, b);
    int lcm_std = std::lcm(a, b);

    assert(gcd_rec == gcd_std);
    assert(gcd_iter == gcd_std);
    assert(lcm == lcm_std);
  }

  std::print("[  PASSED  ]\n");
  return 0;
}
