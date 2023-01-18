#include <iostream>
#include <sys/time.h>
#include "sort_seq.h"
#include "sort_paral.h"
#include "merge_sort_parall.h"
#include "bubble_sort_paral.h"
#include "quick_sort_paral.h"
#include "select_sort_paral.h"
#include "data_to_file.h"

/*
Runing in terminal:
g++ -o main.exe main.cpp sort.cpp
./main.exe
*/

#define LENGTH 10000
#define TESTITE 10
#define UPPER_LIM 10000
#define SEED  100
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

    // srand(SEED);
    struct timeval  start, end;    
    string path = "C://Users/Michal/Desktop/Studia/cpp/sort_01/tests/part_1/";
    string name = path + "length_" + to_string(LENGTH) + "_testite_" + to_string(TESTITE) + "_upperlim_" + to_string(UPPER_LIM) + "_diffseed" + ".txt";
    string fileName = path + name;
    double sumResults = 0;

    cout << fileName;

    for ( int tests = 0; tests < TESTITE; tests++)
    {
        int *arr = new int[LENGTH];
        srand(tests);

        // wygenerowanie zbioru danych - tablica z losowymi wartosciami zawierającymi się w wyznaczonym zakresie wartości
        genereate_data_set(arr, LENGTH, LOWER_LIM, UPPER_LIM);

        //rozpoczęcie pomiaru czasu
        gettimeofday(&start, NULL);

        selection_sort_parall(arr, LENGTH);

        //koniec pomiaru czasu
        gettimeofday(&end, NULL);

        //prezentacja wyników w terminalu
        // print_array(arr, LENGTH);
        
        save_data(to_string(print_time(start, end)), fileName);

        sumResults += print_time(start, end);
        

        delete [] arr;

    }
    save_data(fileName, "Result.txt");
    save_data(to_string(sumResults/TESTITE), "Result.txt");


    return 0;
}




