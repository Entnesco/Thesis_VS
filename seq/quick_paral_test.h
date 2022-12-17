/*
Biblioteka sort_paral.h zawiera implementacje algorytmów sortowanie równoległego
*/

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>


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

