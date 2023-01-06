#include <iostream>
#include <sys/time.h>
#include <pthread.h>
#include "data_gen.h"
#include "time_my.h"
#include "sort_paral.h"
#include "sort_seq.h"

/*
Runing in terminal:
g++ -o main.exe main.cpp sort.cpp
./main.exe
*/

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
    pthread_t threads[NUM_THREADS];

    // wygenerowanie zbioru danych - tablica z losowymi wartosciami zawierającymi się w wyznaczonym zakresie wartości
    genereate_data_set();

    //rozpoczęcie pomiaru czasu
    gettimeofday(&start, NULL);

    selection_sort_parall();

    //koniec pomiaru czasu
    gettimeofday(&end, NULL);

    //prezentacja wyników w terminalu
    print_array();
    print_time(start, end);


    return 0;
}




