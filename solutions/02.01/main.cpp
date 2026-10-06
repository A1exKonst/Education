
// Problem 02.01:
/*
Implement an algorithm to calculate the N-th Fibonacci number based on Binet's formula.
Use the double type for intermediate calculations and the int type for the final Fibonacci number value.
Use the static_cast operator to convert the rounded approximate value of Binet's formula
	from type double to the final value of type int.
Use constants for the values in Binet's formula.
Use the standard functions std::sqrt, std::pow, and std::round.
Justify Binet's formula. 
Use the standard stream std::cin to input the number N via the terminal. 
Use the standard function std::print to output the N-th Fibonacci number to the terminal.
Do not accompany your solution to this problem with tests.
*/


// Binet's formula justification:
/*
Fibonacci sequence: F_n = F_{n-1} + F_{n-2}; F_0 = 0; F_1 = 1;

let F_n = q^n.
Then q^n = q^{n-1} + q^{n-2}.
q^2 - q - 1 = 0.
Roots are: q_1 = (1+\sqrt{5})/2; q_2 = (1-\sqrt{5})/2;
Then solution for F_n is: F_n = C_1 * q_1^n + C_2 * q_2^n.

From F_0 = 0, F_1 = 1 we get C_1 = 1 / \sqrt{5}; C_2 = -1 / \sqrt{5}
*/

#include <iostream>
#include <cmath>
#include <print>

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 0 || n > 46) {
        return 1;
    }
    // (n <= 46) restriction is due to int overflow.

    const double q_1 = (1.0 +  std::sqrt(5.0)) / 2.0;
    const double q_2 = (1.0 -  std::sqrt(5.0)) / 2.0;

    double Fn_double = (std::pow(q_1, n) - std::pow(q_2, n)) /  std::sqrt(5.0);
    int Fn_int = static_cast<int>(std::round(Fn_double));

    std::print("{}\n", Fn_int);

    return 0;
}

