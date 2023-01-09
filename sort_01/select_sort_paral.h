#include <iostream>

using namespace std;

//selection sort parallel algorytm
void selection_sort_parall(int *arr, int n) {
  //iteruj tablice i znajdz wartośc min
  for (int i = 0; i < n - 1; ++i) {
    int min_index = i;
    for (int j = i + 1; j < n; ++j) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }

    //zamien wartosc minimalna z obecna wartoscia
#pragma omp critical
    {
      swap(arr[min_index], arr[i]);
    }
  }
}