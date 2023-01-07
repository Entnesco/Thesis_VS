/*
Biblioteka sort_paral.h zawiera implementacje algorytmów sortowanie równoległego
*/

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>


#define SEED  100
#define LENGTH 1000
#define UPPER_LIM 10000
#define LOWER_LIM  1
#define NUM_THREADS 2

const int NUMBERS_PER_THREAD = LENGTH / NUM_THREADS;
const int OFFSET = LENGTH % NUM_THREADS;
int arr[LENGTH];

void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int middle, int right);
void* thread_merge_sort(void* arg);
void merge_sections_of_array(int arr[], int number, int aggregation);
int generate_random_number(unsigned int lower_limit, unsigned int upper_limit);
void genereate_data_set();
void start_paraller_merge_sort(pthread_t threads[]);
void merge_sort_paral(pthread_t threads[], int aggregation);
void bubble_sort_paral();
void merge2(int l, int m, int r);
void merge_sort2(int l, int r);
int partition(int low, int high);
void quick_sort_parall(int low, int high);
void selection_sort_parall();

using namespace std;

int generate_random_number(unsigned int lower_limit, unsigned int upper_limit) {
    return lower_limit + (upper_limit - lower_limit) * ((double)rand() / RAND_MAX);
}

//merge sort sekwencyjny
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

//łączenie tablic
void merge(int arr[], int left, int middle, int right) {
    int i = 0;
    int j = 0;
    int k = 0;
    int left_length = middle - left + 1;
    int right_length = right - middle;
    int left_array[left_length];
    int right_array[right_length];

    for (int i = 0; i < left_length; i ++) {
        left_array[i] = arr[left + i];
    }

    for (int j = 0; j < right_length; j ++) {
        right_array[j] = arr[middle + 1 + j];
    }

    i = 0;
    j = 0;
    while (i < left_length && j < right_length) {
        if (left_array[i] <= right_array[j]) {
            arr[left + k] = left_array[i];
            i ++;
        } else {
            arr[left + k] = right_array[j];
            j ++;
        }
        k ++;
    }

    while (i < left_length) {
        arr[left + k] = left_array[i];
        k ++;
        i ++;
    }
    while (j < right_length) {
        arr[left + k] = right_array[j];
        k ++;
        j ++;
    }
}

// łączenie posortowanych tablic z wszystkich równoległych wątków
void merge_sections_of_array(int arr[], int number, int aggregation) {
    for(int i = 0; i < number; i = i + 2) {
        int left = i * (NUMBERS_PER_THREAD * aggregation);
        int right = ((i + 2) * NUMBERS_PER_THREAD * aggregation) - 1;
        int middle = left + (NUMBERS_PER_THREAD * aggregation) - 1;
        if (right >= LENGTH) {
            right = LENGTH - 1;
        }
        merge(arr, left, middle, right);
    }
    if (number / 2 >= 1) {
        merge_sections_of_array(arr, number / 2, aggregation * 2);
    }
}

//generowanie zbioru nieposortowanych liczb
void genereate_data_set(){
	for (int i = 0; i < LENGTH; i ++) {
		arr[i] = generate_random_number(LOWER_LIM, UPPER_LIM);
	}
}

// łączenie 2 równoległych wątków
void join_threads(pthread_t threads[]){
	for(long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

// prezentacja tablicy w terminalu
void print_array(){
    for(int i = 0; i < LENGTH ; ++i){
        cout << arr[i] << " ";
    }
    cout << endl;
}

//obliczenie oraz prezentacja czasu operacji
void print_time(struct timeval start, struct timeval end){
	double time_spent;
    time_spent = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 +
                            (double) (end.tv_sec - start.tv_sec)));
    cout << "Time taken for execution: " << time_spent<< " seconds\n";
}

// algorytm merge sort równoległy
void *thread_merge_sort(void* arg)
{
    int thread_id = (long long)arg;
    int left = thread_id * (NUMBERS_PER_THREAD);
    int right = (thread_id + 1) * (NUMBERS_PER_THREAD) - 1;
    if (thread_id == NUM_THREADS - 1) {
        right += OFFSET;
    }
    int middle = left + (right - left) / 2;
    if (left < right) {
        merge_sort(arr, left, right);
        merge_sort(arr, left + 1, right);
        merge(arr, left, middle, right);
    }
    return NULL;
}

//procedura uruchomienia sortowania równoległego
void start_paraller_merge_sort(pthread_t threads[]){
    for (long long i = 0; i < NUM_THREADS; i ++) {
        int rc = pthread_create(&threads[i], NULL, thread_merge_sort, (void *)i);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
}

void merge_sort_paral(pthread_t threads[], int aggregation){
    start_paraller_merge_sort(threads);
    join_threads(threads);
    merge_sections_of_array(arr, NUM_THREADS, aggregation);
}

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

// merge sort parallel 2
void merge2(int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

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

void merge_sort2(int l, int r) {
  if (l < r) {
    //znajdz srodek
    int m = l + (r - l) / 2;

    //podzial tablicy na dwie czesci i sortowanie rownolegle
#pragma omp parallel sections
    {
#pragma omp section
      {
        merge_sort2(l, m);
      }
#pragma omp section
      {
        merge_sort2(m + 1, r);
      }
    }

    //laczenie wczesniej podzielonych czesci
    merge2(l, m, r);
  }
}

//pojedynczy etap quic sort
int partition(int low, int high) {
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
void quick_sort_parall(int low, int high) {
  if (low < high) {
    int pivot_index = partition(low, high);

    //sortowanie swoch częsci rownolegle
#pragma omp parallel sections
    {
#pragma omp section
      {
        quick_sort_parall(low, pivot_index - 1);
      }
#pragma omp section
      {
        quick_sort_parall(pivot_index + 1, high);
      }
    }
  }
}

//selection sort parallel algorytm
void selection_sort_parall() {
  int n = LENGTH;

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