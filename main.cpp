/**
* Title : Algorithm Efficiency and Sorting
* Author : Emre Batuhan Baloglu
* ID: 21502554
* Description : This file contains the test code for performanceAnalysis, quickSort, insertionSort and hybridSort algorithms.
*/

#include <string>
#include <iostream>
#include "sorting.h"
#include <stdlib.h>
#include <ctime>
#include <time.h>
using namespace std;

int main()
{
    //creating three identical arrays
    int* arr1 = new int[12]{22, 11, 6, 7, 30, 2, 27, 24, 9, 1, 20, 17}, comp1 = 0, movecnt1 = 0;
    int* arr2 = new int[12]{22, 11, 6, 7, 30, 2, 27, 24, 9, 1, 20, 17}, comp2 = 0, movecnt2 = 0;
    int* arr3 = new int[12]{22, 11, 6, 7, 30, 2, 27, 24, 9, 1, 20, 17}, comp3 = 0, movecnt3 = 0;

    //insertion sort =====================================
    insertionSort(arr1, 12, comp1, movecnt1);
    printArray(arr1, 12);
    //quick sort ======================================
    quickSort(arr2, 0, 11, comp2, movecnt2);
    printArray(arr2, 12);
    //hybrid sort =====================================
    hybridSort(arr3, 12, comp3, movecnt3);
    printArray(arr3, 12);
    cout<<"Performance analysis \n";
    performanceAnalysis();
    delete[] arr1, arr2, arr3;
    return 0;
}
