#include <algorithm>
#include <iostream>
#include <vector>
#include <omp.h>
#include "test_new_parall.h"

using namespace std;

const int LENGTH = 5;

int test[LENGTH] = {3, 5, 1, 4, 2};



int main(){

  int *arr = new int[LENGTH];

  for(int i = 0; i < LENGTH; i++)
  {
    arr[i]=test[i];
  }

  merge_sort_parall(arr, 0, (LENGTH-1));
  
    for(int i = 0; i < LENGTH; i++)
  {
    cout << arr[i];
  }

  delete [] arr;

}