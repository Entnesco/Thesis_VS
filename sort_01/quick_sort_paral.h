#include <iostream>

using namespace std;

//pojedynczy etap quic sort
int partition(int *arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j < high; ++j) {
    if (arr[j] <= pivot) {
      ++i;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return i + 1;
}

// quick sort parallel algorytm
void quick_sort_parall(int *arr, int low, int high) {
  if (low < high) {
    int pivot_index = partition(arr, low, high);

    //sortowanie swoch częsci rownolegle
#pragma omp parallel sections
    {
#pragma omp section
      {
        quick_sort_parall(arr, low, pivot_index - 1);
      }
#pragma omp section
      {
        quick_sort_parall(arr, pivot_index + 1, high);
      }
    }
  }
}