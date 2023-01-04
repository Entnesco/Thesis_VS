#include <iostream>
#include <stdlib.h>
#include <sys/time.h>


#define SEED  100
#define LENGTH 100
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
void test_array_is_in_order(int arr[]);
int generate_random_number(unsigned int lower_limit, unsigned int upper_limit);
void genereate_data_set();

using namespace std;

int generate_random_number(unsigned int lower_limit, unsigned int upper_limit) {
    return lower_limit + (upper_limit - lower_limit) * ((double)rand() / RAND_MAX);
}

/* realizeaza merge sort */
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

/* functia merge */
void merge(int arr[], int left, int middle, int right) {
    int i = 0;
    int j = 0;
    int k = 0;
    int left_length = middle - left + 1;
    int right_length = right - middle;
    int left_array[left_length];
    int right_array[right_length];

    /* copiaza valorile in array-ul din stanga */
    for (int i = 0; i < left_length; i ++) {
        left_array[i] = arr[left + i];
    }

    /* copiaza valorile in array-ul din dreapta */
    for (int j = 0; j < right_length; j ++) {
        right_array[j] = arr[middle + 1 + j];
    }

    i = 0;
    j = 0;
    /** alege dintre array din stanga si dreapta si copiaza */
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

    /* copiaza valorile ramase in array */
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

void test_array_is_in_order(int arr[]) {
    int max;
    for (int i = 1; i < LENGTH; i ++) {
        if (arr[i] >= arr[i - 1]) {
            max = arr[i];
        } else {
            printf("Error. Out of order sequence: %d found\n", arr[i]);
            return;
        }
    }
    printf("Array is in sorted order\n");
}

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

void genereate_data_set(){
	for (int i = 0; i < LENGTH; i ++) {
		arr[i] = generate_random_number(LOWER_LIM, UPPER_LIM);
	}
}

void join_threads(pthread_t threads[]){
	for(long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

void print_array(){
    for(int i = 0; i < LENGTH ; ++i){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void print_time(struct timeval start, struct timeval end){
	double time_spent;
    time_spent = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 +
                            (double) (end.tv_sec - start.tv_sec)));
    cout << "Time taken for execution: " << time_spent<< " seconds\n";
}

void start_paraller_merge_sort(pthread_t threads[]){
    for (long long i = 0; i < NUM_THREADS; i ++) {
        int rc = pthread_create(&threads[i], NULL, thread_merge_sort, (void *)i);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
}