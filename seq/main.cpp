#include <algorithm>
#include <iostream>
#include <vector>
#include <omp.h>


int const  LENGTH = 5;

int arr[LENGTH] = {3, 5, 1, 4, 2};

int partition(int low, int high) {
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

void quick_sort(int low, int high) {
  if (low < high) {
    int pivot_index = partition(low, high);

    // Sort the two halves concurrently using OpenMP
#pragma omp parallel sections
    {
#pragma omp section
      {
        quick_sort(low, pivot_index - 1);
      }
#pragma omp section
      {
        quick_sort(pivot_index + 1, high);
      }
    }
  }
}

int main() {
  

  quick_sort(0, LENGTH - 1);

  for (int x : arr) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  return 0;
}
