// Problem 02.02:
/*
Implement an algorithm to calculate the roots of a second-degree algebraic
equation with double coefficients a, b, c. Use if branching to check the value
of coefficient a and the value of the discriminant. Use the epsilon constant and
the standard std::abs function to correctly compare double-type numbers with a
given precision. Allow for the occurrence of negative zero. Use the standard
stream std::cin for terminal input of coefficients a, b, and c. Use the standard
function std::print to output all roots of this equation to the terminal. Do not
accompany your solution to this problem with tests.
*/

#include <cmath>
#include <iostream>
#include <print>

auto main() -> int {

  const double epsilon = 1e-9; // Comparison precision
  double a;
  double b;
  double c;

  if (!(std::cin >> a >> b >> c)) {
    return 1;
  }

  if (std::abs(a) < epsilon) { // effectively a == 0
    // bx + c = 0
    if (std::abs(b) < epsilon) {
      return 1; // c = 0. Either no solutions or infinitely many.
    }

    double x = -c / b;
    std::print("{}", x);
    return 0;
  }

  double D = b * b - 4 * a * c;

  if (D <= -epsilon) { // D < 0
    return 1;          // No solutions.
  }

  if (std::abs(D) < epsilon) { // D == 0
    double x = -b / (2 * a);
    std::print("{}", x);
    return 0;
  }

  // D > 0. ( D > +epsilon )
  double sqrt_D = std::sqrt(D);
  double x1 = (-b - sqrt_D) / (2 * a);
  double x2 = (-b + sqrt_D) / (2 * a);
  std::print("{} {}", x1, x2);

  return 0;
}
