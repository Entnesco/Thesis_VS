/*
Biblioteka data_gen.h składa się z klasy DataSetGenererator zawierającej metody związane z generowanie zbioru liczb oraz jego tasowaniem
*/

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;


class DataSetGenerator{
    public:

    int *numbers, n;

    // void shuffleSlow(int size){
    //     int randNum;
    //     numbers.clear(); 
    //     while(numbers.size() < size)    {
    //         randNum = rand() % size + 1;
    //         if(find(numbers.begin(), numbers.end(), randNum) == numbers.end()){
    //             numbers.push_back(randNum);
    //         }
    //     }

        
    // }

    void shuffleFast(int size){ 
        genereteVector(size);
        int randNum, memory;
        for(int i = size - 1; i > 0; i--){
            randNum = rand() % (i + 1);
            memory = numbers[randNum];
            numbers[randNum] = numbers[i];
            numbers[i] = memory;
        }
    }

    void printTab(){
        for(int i = 0; i < n ; ++i){
            cout << numbers[i] << " ";
        }
        cout << endl;
    }

    void printAllTab(int arr[], int size){
        for(int i = 0; i < size ; ++i){
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    int * getTab()
    {
        return numbers;
    }

    void genereteVector(int size){
        n = size;
        numbers = new int [size];
        for(int i = 0; i < size; i++){
            numbers[i] = i+1;
        }
    }

    void generateRandomDS(int size, int range)
    {
        n = size;
        numbers = new int [size];
        for(int i = 0; i < size; i++){
            numbers[i] = rand() % (range); 
        }
    }
};
