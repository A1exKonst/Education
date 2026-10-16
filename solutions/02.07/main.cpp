// Problem 02.07
/*
Continuation of 02.06: bubble_sort, mean, median, min, max.
with dynamic arrays.


NOTE: It is supposed, that array input ends with not-a-number.

NOTE: According to requirements, all code should be in one file, which it is.
*/

#include <cmath>
#include <iostream>
#include <print>

class DynamicArray;

void bubble_sort(double *numbers, size_t size);

/*
WARNING:
Class DynamicArray was created only for better code isolation.
It does not support standard std::vector operations.
It was only created to better isolate code in a given task 02.07.
*/
class DynamicArray {
private:
  double *data_{nullptr};
  size_t cap{0};
  size_t sz{0};

  void resize() {
    cap = (cap == 0) ? 4 : cap * 2;
    auto *new_data = new double[cap];

    for (size_t i = 0; i < sz; ++i) {
      new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
  }

public:
  DynamicArray() = default;

  ~DynamicArray() {
    if (data_) {
      delete[] data_;
    }
  }

  void push_back(double value) {
    if (sz >= cap) {
      resize();
    }
    data_[sz] = value;
    sz++;
  }

  [[nodiscard]] auto size() const -> size_t { return sz; }

  auto operator[](size_t index) -> double & { return data_[index]; }

  auto operator[](size_t index) const -> const double & { return data_[index]; }

  auto data() noexcept -> double * { // c-style
    return data_;
  }

  [[nodiscard]] auto data() const noexcept -> const double * { // c-style
    return data_;
  }
};

/*
WARNING:
This implementation does not support sort and parallel modification (i.e.
push_back) Function bubble_sort(...) was created only for better code isolation.
It does not guarantee compatibility with DynamicArray in each given situation.
It does guarantee compatibility in circumstances of a given task 02.07.
*/
void bubble_sort(double *numbers, size_t size) {
  for (size_t i = 0; i < size - 1; ++i) {
    bool swapped = false;

    for (size_t j = 0; j < size - i - 1; ++j) {
      if (numbers[j] > numbers[j + 1]) {
        double temp = numbers[j];
        numbers[j] = numbers[j + 1];
        numbers[j + 1] = temp;
        swapped = true;
      }
    }

    if (!swapped)
      break;
  }
}

auto main() -> int {
  DynamicArray array;
  double value;

  // input:
  while (std::cin >> value) {
    array.push_back(value);
  }

  size_t size = array.size();
  if (size == 0) {
    std::println("DynamicArray is empty");
    return 0;
  }

  // min, max, average:
  double min_val = array[0];
  double max_val = array[0];
  double sum = 0.0;

  for (size_t i = 0; i < size; ++i) {
    if (array[i] < min_val)
      min_val = array[i];
    if (array[i] > max_val)
      max_val = array[i];
    sum += array[i];
  }
  double average = sum / static_cast<double>(size);
  // 64 petabyte of memory (which is when size overflows double) in this task is
  // considered impossible

  // variance:
  double variance_sum = 0.0;
  for (size_t i = 0; i < size; ++i) {
    variance_sum += (array[i] - average) *
                    (array[i] - average); // std::pow(..., 2) is suboptimal
  }
  double std_deviation = std::sqrt(variance_sum / static_cast<double>(size));

  // median:
  bubble_sort(array.data(), array.size());

  double median;
  if (size % 2 != 0) {
    median = array[size / 2];
  } else {
    median = (array[(size / 2) - 1] + array[size / 2]) / 2.0;
  }

  std::print("min:     {}\n", min_val);
  std::print("max:     {}\n", max_val);
  std::print("average: {}\n", average);
  std::print("std:     {}\n", std_deviation);
  std::print("median:  {}\n", median);

  /* assertions:
      it is supposed, that "do not apply tests to your code" from task text
      is inherited from original task 02.06.

      though no assertions are written, manual tests with -fsanitize were
     performed
 */
  return 0;
}
