// quickselect algorithm for O(N) median search.



#include <iostream>
#include <cmath>
#include <print>



void bubble_sort(double* numbers, int size) {
    for (int i = 0; i < size - 1; ++i) {
        bool swapped = false;
        
        for (int j = 0; j < size - i - 1; ++j) {
            if (numbers[j] > numbers[j + 1]) {
                double temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                swapped = true;
            }
        }
        
        if (!swapped) break;
    }
}



int main() {

    // statically defined array
    const int MAX_SIZE = 1000;
    double numbers[MAX_SIZE];
    int size = 0;

    if (!(std::cin >> size) || size <= 0 || size > MAX_SIZE) {
        return 1;
    }

    // Calculation of min, max, average
    std::cin >> numbers[0];
    double min_val = numbers[0];
    double max_val = numbers[0];
    double sum = numbers[0];

    // min, max, average combined with input:
    for (int i = 1; i < size; ++i) {
        std::cin >> numbers[i];
        if (numbers[i] < min_val) min_val = numbers[i];
        if (numbers[i] > max_val) max_val = numbers[i];
        sum += numbers[i];
    }
    double mean = sum / size;

    double variance_sum = 0.0;
    for (int i = 0; i < size; ++i) {
        variance_sum += (numbers[i] - mean) * (numbers[i] - mean);
    }
    double std_dev = std::sqrt(variance_sum / size);

    // optional, but before sort array is copied:
    double sorted_numbers[MAX_SIZE];
    for (int i = 0; i < size; ++i) {
        sorted_numbers[i] = numbers[i];
    }

    bubble_sort(sorted_numbers, size);

    // median
    double median;
    if (size % 2 != 0) {
        median = sorted_numbers[size / 2];
    } else {
        median = (sorted_numbers[(size / 2) - 1] + sorted_numbers[size / 2]) / 2.0;
    }

    // output
    std::print("min:    {:.4f}\n", min_val);
    std::print("max:    {:.4f}\n", max_val);
    std::print("mean:   {:.4f}\n", mean);
    std::print("std:    {:.4f}\n", std_dev);
    std::print("median: {:.4f}\n", median);

    return 0;
}
