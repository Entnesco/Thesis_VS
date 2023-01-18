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


#define LENGTH_MIN 1000
#define LENGTH_MAX 10000
#define LENGTH_STEP 1000
#define TESTITE 10
#define UPPER_LIM 1000
#define LOWER_LIM  1
#define SEED  100
string algortih_name = "quick_sort_parall";

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
    string test_type = algortih_name + ";lengthmin=" + to_string(LENGTH_MIN) + ";lengthmax=" + to_string(LENGTH_MAX) + ";testite=" + to_string(TESTITE) + ";upperlim=" + to_string(UPPER_LIM) + ";diffseed";
    save_data(test_type, "C://Users/Michal/Desktop/Studia/cpp/sort_01/tests/part_2/Result.txt");
    save_data("seconds  length", "C://Users/Michal/Desktop/Studia/cpp/sort_01/tests/part_2/Result.txt");

    for( int length = LENGTH_MIN; length <= LENGTH_MAX; length += LENGTH_STEP)
    {
        string path = "C://Users/Michal/Desktop/Studia/cpp/sort_01/tests/part_1/";
        string name = "length_" + to_string(length) + "_testite_" + to_string(TESTITE) + "_upperlim_" + to_string(UPPER_LIM) + "_diffseed" + ".txt";
        string fileName = path + name;
        double sumResults = 0;

        for ( int test = 0; test <= length; test++)
        {
            int *arr = new int[length];
            srand(test);

            // wygenerowanie zbioru danych - tablica z losowymi wartosciami zawierającymi się w wyznaczonym zakresie wartości
            genereate_data_set(arr, length, LOWER_LIM, UPPER_LIM);

            //rozpoczęcie pomiaru czasu
            gettimeofday(&start, NULL);

            quick_sort_parall(arr, 0,length-1);

            //koniec pomiaru czasu
            gettimeofday(&end, NULL);

            //prezentacja wyników w terminalu
            // print_array(arr, LENGTH);
            
            save_data(to_string(print_time(start, end)), fileName);

            sumResults += print_time(start, end);
            

            delete [] arr;

        }
        save_data(to_string(sumResults/TESTITE) + "  " + to_string(length), "C://Users/Michal/Desktop/Studia/cpp/sort_01/tests/part_2/Result.txt");
    }


    return 0;
}




