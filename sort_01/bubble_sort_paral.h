#include <iostream>

using namespace std;

// bubble sort
void bubble_sort_paral(int *arr, int length)
{
    
    bool zmiana; // zmienna pomocnicza do sprawdzenia, czy zaszła zmiana w kolejnym przebiegu pętli
    do
    {
        zmiana = false;

        // sortujemy elementy wektora równolegle za pomocą OpenMP
        #pragma omp parallel for shared(arr, zmiana)
        for (int i = 1; i < length; i++)
        {
            if (arr[i] < arr[i - 1])
            {
                // zamieniamy miejscami elementy, jeśli są one w złej kolejności
                swap(arr[i], arr[i - 1]);
                zmiana = true; // zapamiętujemy, że zaszła zmiana
            }
        }
    } while (zmiana); // pętla wykonuje się tak długo, aż nie zaszła żadna zmiana w kolejnym przebiegu
}