// Problem 02.10:
/*
Refine example 02.44 so that the implementation uses the quicksort algorithm instead of the merge sort algorithm.
Implement Hoare's partition scheme.
Use the median of the first, middle, and last elements as the pivot element.
Justify the time complexity of this sorting algorithm.
*/



// Example 02.44 declares these functions:
/*
void order(std::vector < int > & vector, std::size_t left, std::size_t right);

void merge(std::vector < int > & vector_1, std::size_t left, std::size_t right);

void split(std::vector < int > & vector, std::size_t left, std::size_t right);

void sort(std::vector < int > & vector);

int main() {
	auto size = 1uz << 10;
	std::vector < int > vector(size, 0);
	for (auto i = 0uz; i < size; ++i)
		vector[i] = size - i;
	sort(vector);
	assert(std::ranges::is_sorted(vector));
}
*/



#include <vector>
#include <numeric>
#include <cassert>
#include <algorithm>
#include <print>



void sort(std::vector<int> &vector);
void split(std::vector<int> &vector, std::size_t left, std::size_t right); // Recursive split for Quick Sort
void order(std::vector<int> &vector, std::size_t left, std::size_t right); // Insertion sort for small arrays
std::size_t partition(std::vector<int> &vector, std::size_t left, std::size_t right); // Hoare partition for interval [left, right)
int median_of_three(std::vector<int> &vector, std::size_t left, std::size_t right); // Choose median of three and put it at the start of the range



int main() {
        auto size = 1uz << 10; // 1024
        std::vector<int> vector(size, 0);
        for (auto i = 0uz; i < size; ++i)
                vector[i] = static_cast<int>(size - i);

	for (auto i = 0uz; i < size; ++i)
                std::print("{}, ", vector[i]);
	std::print("\n");

        sort(vector);
        assert(std::ranges::is_sorted(vector));

	for (auto i = 0uz; i < size; ++i)
                std::print("{}, ", vector[i]);
	std::print("\n [ PASSED ]\n");
	return 0;
}



// Pubic interface:
void sort(std::vector<int> &vector) {
        if (vector.empty()) return;
        split(vector, 0, std::size(vector)); 

	/* O(N*log(N)) complexity:
	split(...) is called O(log(N)) times, as ranges are split in half.
	each split performs a partition(...), which has an O(N) complexity.

	To ensure that split(...) chooses a pivot via O(log(N)),
	function median_of_three(...) is used.
	*/
}



// Recursive split for quicksort via Hoare's algorithm.
void split(std::vector<int> &vector, std::size_t left, std::size_t right) {
        if (right - left > 16) {
                // in Hoare's algorithm it is guaranteed, that all of [left, p] <= all of [p + 1, right)
                std::size_t p = partition(vector, left, right);
                split(vector, left, p + 1);
                split(vector, p + 1, right);
        }
        else {
                order(vector, left, right); // small arrays are faster to sort through insertion sort.
        }
}



// Insertion sort for small arrays:
// Insertion sort is a part of quicksort algorithm, when arrays are small.
void order(std::vector<int> &vector, std::size_t left, std::size_t right) {
        for (auto i = left + 1; i < right; ++i) {
                for (auto j = i; j > left; --j) {
                        if (vector[j - 1] > vector[j]) 
                                std::swap(vector[j], vector[j - 1]);
                }
        }
}



// Hoare's partition for interval [left, right)
/* Sorts given part of an array so that:
vector[left, j] <= pivot
vector[j+1, right] >= pivot
vector[j] == pivot */
std::size_t partition(std::vector<int> &vector, std::size_t left, std::size_t right) {
        int pivot = median_of_three(vector, left, right);

        std::ptrdiff_t i = static_cast<std::ptrdiff_t>(left) - 1;
        std::ptrdiff_t j = static_cast<std::ptrdiff_t>(right); 

        while (true) {
		/* these 3 cycles altogether have an O(N) complexity,
		because i and j are only increased or decreased (up to N operations) */
                do { ++i; } while (vector[static_cast<std::size_t>(i)] < pivot);
                do { --j; } while (vector[static_cast<std::size_t>(j)] > pivot);

                if (i >= j) 
                        return static_cast<std::size_t>(j);

                std::swap(vector[static_cast<std::size_t>(i)], vector[static_cast<std::size_t>(j)]);
        }
}



// Helper function, optimizes the choice of pivot.
/* if by default pivot is chosen as vector[left], than it has O(N^2) complexity on already sorted arrays.
it is more optimal in this case to use a median of three elements as a pivot */
int median_of_three(std::vector<int> &vector, std::size_t left, std::size_t right) {
        auto mid = left + (right - left) / 2;
        auto last = right - 1;

        if (vector[mid] < vector[left])  std::swap(vector[left], vector[mid]);
        if (vector[last] < vector[left]) std::swap(vector[left], vector[last]);
        if (vector[mid] < vector[last])  std::swap(vector[mid], vector[last]);

        // now median is in vector[last]
        return vector[last];
}
