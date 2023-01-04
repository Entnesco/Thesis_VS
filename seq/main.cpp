#include <algorithm>
#include <iostream>
#include <vector>
#include <omp.h>

int partition(std::vector<int>& arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j < high; ++j) {
    if (arr[j] <= pivot) {
      ++i;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]);
  return i + 1;
}

void quick_sort(std::vector<int>& arr, int low, int high) {
  if (low < high) {
    int pivot_index = partition(arr, low, high);

    // Sort the two halves concurrently using OpenMP
#pragma omp parallel sections
    {
#pragma omp section
      {
        quick_sort(arr, low, pivot_index - 1);
      }
#pragma omp section
      {
        quick_sort(arr, pivot_index + 1, high);
      }
    }
  }
}

int main() {
  std::vector<int> arr = {3, 5, 1, 4, 2};

  quick_sort(arr, 0, arr.size() - 1);

  for (int x : arr) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  return 0;
}
