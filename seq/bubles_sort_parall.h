#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

int main()
{
    vector<int> v = {3, 2, 5, 1, 4}; // wektor do posortowania

    bool zmiana; // zmienna pomocnicza do sprawdzenia, czy zaszła zmiana w kolejnym przebiegu pętli
    do
    {
        zmiana = false;

        // sortujemy elementy wektora równolegle za pomocą OpenMP
        #pragma omp parallel for shared(v, zmiana)
        for (int i = 1; i < v.size(); i++)
        {
            if (v[i] < v[i - 1])
            {
                // zamieniamy miejscami elementy, jeśli są one w złej kolejności
                swap(v[i], v[i - 1]);
                zmiana = true; // zapamiętujemy, że zaszła zmiana
            }
        }
    } while (zmiana); // pętla wykonuje się tak długo, aż nie zaszła żadna zmiana w kolejnym przebiegu

    // wyświetlamy posortowany wektor
    for (int x : v)
        cout << x << " ";
    cout << endl;

    return 0;
}
