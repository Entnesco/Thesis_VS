/*
Biblioteka sort_paral.h zawiera implementacje algorytmów sortowanie równoległego
*/

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <algorithm>
#include <omp.h>


#define SEED  100
#define LENGTH 20
#define UPPER_LIM 20
#define LOWER_LIM  1
#define NUM_THREADS 2

const int NUMBERS_PER_THREAD = LENGTH / NUM_THREADS;
const int OFFSET = LENGTH % NUM_THREADS;
const int MID = LENGTH/2;
int arr[LENGTH];

int generate_random_number(unsigned int lower_limit, unsigned int upper_limit);
void genereate_data_set();
void quick_sort(int *tab, int lewy, int prawy);
void quick_sort_paral(int *tab, int lewy, int prawy);
void print_array();
void bubble_sort_first();
void merge(int l, int m, int r);
void merge_sort(int l, int r);

using namespace std;

int generate_random_number(unsigned int lower_limit, unsigned int upper_limit) {
    return lower_limit + (upper_limit - lower_limit) * ((double)rand() / RAND_MAX);
}

//generowanie zbioru nieposortowanych liczb
void genereate_data_set(){
	for (int i = 0; i < LENGTH; i ++) {
		arr[i] = generate_random_number(LOWER_LIM, UPPER_LIM);
	}
}

void print_array(){
    for(int i = 0; i < LENGTH ; ++i){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void quick_sort(int *tab, int lewy, int prawy)
{
	if(prawy <= lewy) return;
	
	int i = lewy - 1, j = prawy + 1, 
	pivot = tab[(lewy+prawy)/2]; //wybieramy punkt odniesienia
	
	while(1)
	{
		//szukam elementu wiekszego lub rownego piwot stojacego
		//po prawej stronie wartosci pivot
		while(pivot>tab[++i]);
		
		//szukam elementu mniejszego lub rownego pivot stojacego
		//po lewej stronie wartosci pivot
		while(pivot<tab[--j]);
		
		//jesli liczniki sie nie minely to zamień elementy ze soba
		//stojace po niewlasciwej stronie elementu pivot
		if( i <= j)
			//funkcja swap zamienia wartosciami tab[i] z tab[j]
			swap(tab[i],tab[j]);
		else
			break;
	}

	if(j > lewy)
		quick_sort(tab, lewy, j);
	if(i < prawy)
		quick_sort(tab, i, prawy);
}

void *quick_sort_paral(void* arg)
{
    int prawy, lewy;
    int thread_id = (long long)arg;

    if(thread_id == 0)
    {
        lewy = 0;
        prawy = MID;
    }
    else
    {
        lewy = MID;
        prawy = LENGTH;
    }

	
	int i = lewy - 1, j = prawy + 1, 
	pivot = arr[(lewy+prawy)/2]; //wybieramy punkt odniesienia
	
	while(1)
	{
		//szukam elementu wiekszego lub rownego piwot stojacego
		//po prawej stronie wartosci pivot
		while(pivot>arr[++i]);
		
		//szukam elementu mniejszego lub rownego pivot stojacego
		//po lewej stronie wartosci pivot
		while(pivot<arr[--j]);
		
		//jesli liczniki sie nie minely to zamień elementy ze soba
		//stojace po niewlasciwej stronie elementu pivot
		if( i <= j)
			//funkcja swap zamienia wartosciami tab[i] z tab[j]
			swap(arr[i],arr[j]);
		else
			break;
	}

	if(j > lewy)
		quick_sort(arr, lewy, j);
	if(i < prawy)
		quick_sort(arr, i, prawy);
    
    return NULL;
}

//wybieramy wartośc środkową mniejsze niż sortujemy a pózniej sortujemy więkrze niż



// bubble sort
void bubble_sort_paral()
{
    
    bool zmiana; // zmienna pomocnicza do sprawdzenia, czy zaszła zmiana w kolejnym przebiegu pętli
    do
    {
        zmiana = false;

        // sortujemy elementy wektora równolegle za pomocą OpenMP
        #pragma omp parallel for shared(arr, zmiana)
        for (int i = 1; i < LENGTH; i++)
        {
            if (arr[i] < arr[i - 1])
            {
                // zamieniamy miejscami elementy, jeśli są one w złej kolejności
                swap(arr[i], arr[i - 1]);
                zmiana = true; // zapamiętujemy, że zaszła zmiana
            }
        }
    } while (zmiana); // pętla wykonuje się tak długo, aż nie zaszła żadna zmiana w kolejnym przebiegu
}

void merge(int l, int m, int r) {
  // Find sizes of two subarrays to be merged
  int n1 = m - l + 1;
  int n2 = r - m;

  // Create temp arrays
  int L[n1], R[n2];

  // Copy data to temp arrays
  for (int i = 0; i < n1; ++i) {
    L[i] = arr[l + i];
  }
  for (int i = 0; i < n2; ++i) {
    R[i] = arr[m + 1 + i];
  }

  // Merge the temp arrays back into arr[l..r]
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

  // Copy the remaining elements of L, if there are any
  while (i < n1) {
    arr[k] = L[i];
    ++i;
    ++k;
  }

  // Copy the remaining elements of R, if there are any
  while (j < n2) {
    arr[k] = R[j];
    ++j;
    ++k;
  }
}

void merge_sort(int l, int r) {
  if (l < r) {
    // Find the middle point
    int m = l + (r - l) / 2;

    // Split the array into two halves and sort them concurrently using OpenMP
#pragma omp parallel sections
    {
#pragma omp section
      {
        merge_sort(l, m);
      }
#pragma omp section
      {
        merge_sort(m + 1, r);
      }
    }

    // Merge the sorted halves
    merge(l, m, r);
  }
}