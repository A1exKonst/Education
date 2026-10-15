// Problem 02.08
/*
Implement an algorithm to calculate the maximum Collatz sequence length
        among all sequences starting with values from 1 to 100.
Use the unsigned long long int type for Collatz sequence values and the standard
std::size_t type for their lengths. Use the standard std::vector container to
cache Collatz sequence lengths and optimize the calculation of each new sequence
length based on previous sequences. Use the standard std::print function to
output to the terminal the maximum Collatz sequence length among those
considered, as well as the value it starts with. Do not accompany your solution
to this problem with tests.
*/

/*
NOTE 1:
Collatz sequence is defined as follows:
        if (n % 2 == 0) n = n / 2
        else n = 3*n + 1;
*/

/*
NOTE 2:
In this implementation cache.size() is constant.
Not all Collatz sequence values are stored in cache, but only values [1;
upper_calculated_bound].

This decision was made due to probability of receiving high values during
Collatz sequence. Storing all Collatz sequence cache would require 10'000
elements in std::vector. It was supposed, that allocation of this size will take
more time, than simply computing and discarding high values (value > 100).
*/

#include <iostream>
#include <print>
#include <vector>

using ull_t = unsigned long long;

int main() {
  const ull_t upper_bound =
      100; // calculate all Collatz sequences for n in [1;100]

  // cache[i] = length_i => the length of Collatz sequence with a start {n = i}
  // is {length_i}
  std::vector<std::size_t> cache(upper_bound + 1, 0);
  cache[1] = 1; // base case

  ull_t max_start_value = 1;
  std::size_t max_length = 1;

  for (ull_t i = 2; i <= upper_bound; ++i) {
    ull_t n = i;
    std::size_t steps = 0;

    // calculate Collatz sequence until already calculated (cached) value is
    // found:
    while (n >= i || cache[n] == 0) {
      if (n % 2 == 0) {
        n /= 2;
      } else {
        n = 3 * n + 1;
      }
      ++steps;
    }

    cache[i] = steps + cache[n];

    if (cache[i] > max_length) { // calculating max Collatz sequence - it is an
                                 // output parameter
      max_length = cache[i];
      max_start_value = i;
    }
  }

  std::print("{} {}\n", max_length, max_start_value);

  return 0;
}
