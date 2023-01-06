#include <algorithm>
#include <iostream>
#include <vector>
#include <omp.h>

const int LENGTH = 5;

int arr[LENGTH] = {3, 5, 1, 4, 2};

void selection_sort() {
  int n = LENGTH;

  // Loop through the array and find the minimum element in each iteration
  for (int i = 0; i < n - 1; ++i) {
    int min_index = i;
    for (int j = i + 1; j < n; ++j) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }

    // Swap the minimum element with the current element
#pragma omp critical
    {
      std::swap(arr[min_index], arr[i]);
    }
  }
}

int main() {

  selection_sort();

  for (int x : arr) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  return 0;
}