#include <iostream>
#include <algorithm>
#include <vector>
#include <pthread.h>

using namespace std;

void *thread_task(void* arg);

int main()
{
	int threds_num = 5;
	pthread_t threads[threds_num];

	for (long long i = 0; i < threds_num; i ++) {
        int rc = pthread_create(&threads[i], NULL, thread_task, (void *)i);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

	for(long i = 0; i < threds_num; i++) {
        pthread_join(threads[i], NULL);
    }

	
	return 0;
}

void *thread_task(void* arg)
{
    int thread_id = (long long)arg;
	cout << thread_id << endl;

	return NULL;
}
