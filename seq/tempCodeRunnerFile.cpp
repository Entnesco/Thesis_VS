#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <iostream>
#include "test.h"




using namespace std;



int main(int argc, const char * argv[]) {
    srand(SEED);
    struct timeval  start, end;
    pthread_t threads[NUM_THREADS];

    genereate_data_set();

    gettimeofday(&start, NULL);

    /* creaza thread-urile */
    start_paraller_merge_sort(threads);

    join_threads(threads);

    merge_sections_of_array(arr, NUM_THREADS, 1);

    gettimeofday(&end, NULL);

    print_array();

    print_time(start, end);

    return 0;
}
