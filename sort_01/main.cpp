#include <iostream>
#include <sys/time.h>
#include "sort_seq.h"
#include "sort_paral.h"
#include "merge_sort_parall.h"
#include "bubble_sort_paral.h"
#include "quick_sort_paral.h"
#include "select_sort_paral.h"

/*
Runing in terminal:
g++ -o main.exe main.cpp sort.cpp
./main.exe
*/

#define SEED  100
#define LENGTH 1000
#define UPPER_LIM 10000
#define LOWER_LIM  1

using namespace std;



int main(){

    // Tim.startTimer();
    // Gen.shuffleSlow(12);
    // cout << "Nano: " << Tim.stopGetMicroseconds() << endl;

    // Gen.generateRandomDS(liczba, zakres);
    // Gen.printTab();

    // selection_sort(Gen.numbers, liczba);
    // Gen.printTab();

    srand(SEED);
    struct timeval  start, end;
    int *arr = new int[LENGTH];

    // wygenerowanie zbioru danych - tablica z losowymi wartosciami zawierającymi się w wyznaczonym zakresie wartości
    genereate_data_set(arr, LENGTH, LOWER_LIM, UPPER_LIM);

    //rozpoczęcie pomiaru czasu
    gettimeofday(&start, NULL);

    selection_sort_parall(arr, LENGTH);

    //koniec pomiaru czasu
    gettimeofday(&end, NULL);

    //prezentacja wyników w terminalu
    print_array(arr, LENGTH);
    print_time(start, end);

    delete [] arr;


    return 0;
}




