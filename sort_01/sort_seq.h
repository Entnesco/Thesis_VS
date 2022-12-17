/*
Biblioteka sort_seq.h zawiera implementacje zwykłych algorytmów sortowania
*/

#include <iostream>
#include <stdlib.h>

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

//////////////////////////////////////////////////////////

int *pom; //tablica pomocnicza, wykorzystywana przy funkcji odpowiedzialnej za scalanie

//scalenie posortowanych podtablic
void merge_seq(int *tab, int lewy, int srodek, int prawy) 
{
	int i = lewy, j = srodek + 1;
 
  //tworzenie tablicy pomocniczej
  for(int i = lewy;i<=prawy; i++) 
    pom[i] = tab[i];  
  
  //scalanie tablic pomocniczy i nasępnie zapisanie ich do własciwej tablicy
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

//pom = new int [liczba];
void merge_sort_seq(int *tab,int lewy, int prawy)
{	
	//sprawdzamy czy zbiór składa się z jednego elementu
	if(prawy<=lewy) return; 
	
	//obliczamy środek tablicy
	int srodek = (prawy+lewy)/2;
	
	//podział tablicy na część lewą i prawą względem środka
	merge_sort_seq(tab, lewy, srodek); 
	merge_sort_seq(tab, srodek+1, prawy);
	
	//scalamy posortowanych tablic
	merge_seq(tab, lewy, srodek, prawy);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void bubble_sort(int *tab,int n)
{
	for(int i=0;i<n;i++)
		for(int j=1;j<n-i;j++)
		if(tab[j-1]>tab[j])
			//zamiana miejscami
			swap(tab[j-1], tab[j]);
}

void selection_sort(int *tab,int n) //n - ilość elementów do posortowania
{
int mn_index; //zmienna pomocnicza przechowująca informacje o indeksie komóeki z najmniejszą wartością
  for(int i=0;i<n-1;i++)
  {
  	mn_index = i;
    for(int j=i+1;j<n;j++) //wyszukiwanie elemntu a najniższej wartośći
    if(tab[j]<tab[mn_index])
      mn_index = j;
 
    //zamiana pierwszego elementu zbioru z wartoscią najmniejsza w zbiorze
	swap(tab[i], tab[mn_index]);
  }
}

