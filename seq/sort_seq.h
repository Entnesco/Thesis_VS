#include <iostream>
#include <stdlib.h>

#define LENGTH 20
#define UPPER_LIM 100
#define LOWER_LIM  1
int arr[LENGTH];

using namespace std;

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

int *pom; //tablica pomocnicza, potrzebna przy scalaniu

//scalenie posortowanych podtablic
void scal(int tab[], int lewy, int srodek, int prawy) 
{
	int i = lewy, j = srodek + 1;
 
  //kopiujemy lewą i prawą część tablicy do tablicy pomocniczej
  for(int i = lewy;i<=prawy; i++) 
    pom[i] = tab[i];  
  
  //scalenie dwóch podtablic pomocniczych i zapisanie ich 
  //we własciwej tablicy
  for(int k=lewy;k<=prawy;k++) 
  if(i<=srodek)
    if(j <= prawy)
         if(pom[j]<pom[i])
             tab[k] = pom[j++];
         else
             tab[k] = pom[i++];
    else
        tab[k] = pom[i++];
  else
      tab[k] = pom[j++];
}

void sortowanie_przez_scalanie(int tab[],int lewy, int prawy)
{
	//gdy mamy jeden element, to jest on już posortowany
	if(prawy<=lewy) return; 
	
	//znajdujemy srodek podtablicy
	int srodek = (prawy+lewy)/2;
	
	//dzielimy tablice na częsć lewą i prawa
	sortowanie_przez_scalanie(tab, lewy, srodek); 
	sortowanie_przez_scalanie(tab, srodek+1, prawy);
	
	//scalamy dwie już posortowane tablice
	scal(tab, lewy, srodek, prawy);
}

int generate_random_number(unsigned int lower_limit, unsigned int upper_limit) {
    return lower_limit + (upper_limit - lower_limit) * ((double)rand() / RAND_MAX);
}

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