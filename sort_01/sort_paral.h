/*
Biblioteka sort_paral.h zawiera implementacje algorytmów sortowanie równoległego
*/

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>

int generate_random_number(unsigned int lower_limit, unsigned int upper_limit);
void genereate_data_set(unsigned int lower_limit, unsigned int upper_limit);

using namespace std;

int generate_random_number(unsigned int lower_limit, unsigned int upper_limit) {
    return lower_limit + (upper_limit - lower_limit) * ((double)rand() / RAND_MAX);
}

//generowanie zbioru nieposortowanych liczb
void genereate_data_set(int *arr, int length, unsigned int lower_limit, unsigned int upper_limit){
	for (int i = 0; i < length; i ++) {
		arr[i] = generate_random_number(lower_limit, upper_limit);
	}
}

// prezentacja tablicy w terminalu
void print_array(int *arr, int length){
    for(int i = 0; i < length ; ++i){
        cout << arr[i] << " ";
    }
    cout << endl;
}

//obliczenie oraz prezentacja czasu operacji
double print_time(struct timeval start, struct timeval end){
	double time_spent;
    time_spent = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 +
                            (double) (end.tv_sec - start.tv_sec)));
    cout << "Time taken for execution: " << time_spent<< " seconds\n";
    return time_spent;
}