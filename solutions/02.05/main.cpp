// Problem 02.05
/*
pi and e calculations according to Leibniz series terms and Maclaurin series
terms
*/

#include <cmath>
#include <iostream>
#include <print>

auto calculate_pi(const double epsilon) -> double;

auto calculate_e(const double epsilon) -> double;

auto calculate_pi(const double epsilon) -> double {
  // Lebniz series terms:
  // pi = 4 * (1 - 1/3 + 1/5 - 1/7 + ... ) + (-1)^n / (2n + 1)

  double pi_sum = 0.0;
  double pi_term = 1.0;
  int n = 0;
  int sign = 1;

  while (pi_term >= epsilon) {
    pi_sum += sign * pi_term;
    n++;
    pi_term = 1.0 / (2 * n + 1);
    sign = -sign;
  }

  return 4.0 * pi_sum;
}

auto calculate_e(const double epsilon) -> double {
  // Mauclaurin series terms:
  // e = 1/0! + 1/1! + 1/2! + 1/3! + ...
  // term_n = term_{n-1} / n

  double e_sum = 0.0;
  double e_term = 1.0;
  int k = 1;

  while (e_term >= epsilon) {
    e_sum += e_term;
    e_term /= k;
    k++;
  }

  return e_sum;
}

auto main() -> int {

  double epsilon = 0.0;

  if (!(std::cin >> epsilon) || epsilon <= 0.0) {
    return 1;
  }

  std::print("pi: {}\n", calculate_pi(epsilon));
  std::print("e:  {}\n", calculate_e(epsilon));

  return 0;
}
