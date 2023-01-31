#include <iostream>
#include <vector>

using namespace std;

// merge sort parallel 2
void merge_parall(int *arr, int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  vector<int> L(n1), R(n2);

  //kopjuj dane do pomocniczych tablic
  for (int i = 0; i < n1; ++i) {
    L[i] = arr[l + i];
  }
  for (int i = 0; i < n2; ++i) {
    R[i] = arr[m + 1 + i];
  }

  //łącz tablice
  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      ++i;
    } else {
      arr[k] = R[j];
      ++j;
    }
    ++k;
  }

  //kopiuj pozostałe elementy
  while (i < n1) {
    arr[k] = L[i];
    ++i;
    ++k;
  }

  //kopiuj pozostałe elementy
  while (j < n2) {
    arr[k] = R[j];
    ++j;
    ++k;
  }
}

void merge_sort_parall(int *arr, int l, int r) {
  if (l < r) {
    //znajdz srodek
    int m = l + (r - l) / 2;

    //podzial tablicy na dwie czesci i sortowanie rownolegle
#pragma omp parallel sections
    {
#pragma omp section
      {
        merge_sort_parall(arr, l, m);
      }
#pragma omp section
      {
        merge_sort_parall(arr, m + 1, r);
      }
    }

    //laczenie wczesniej podzielonych czesci
    merge_parall(arr, l, m, r);
  }
}