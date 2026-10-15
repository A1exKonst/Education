// Problem 02.04: Armstrong numbers
/*
An Armstrong number is a number, which is equal to the sum of cubes of its
digits.
*/

#include <print>

int main() {

  // Variables are used so that:
  // number = 100*i + 10*j + k

  for (int i = 1; i <= 9; ++i) {
    for (int j = 0; j <= 9; ++j) {
      for (int k = 0; k <= 9; ++k) {

        // std::pow is prohibited:
        int cube_i = i * i * i;
        int cube_j = j * j * j;
        int cube_k = k * k * k;

        int number = i * 100 + j * 10 + k;

        if (cube_i + cube_j + cube_k == number) {
          std::print("{}\n", number);
        }
      }
    }
  }

  return 0;
}
