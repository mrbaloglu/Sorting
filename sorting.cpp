/**
* Title : Algorithm Efficiency and Sorting
* Author : Emre Batuhan Baloglu
* Description : This file contains the code for quickSort, insertionSort and hybridSort algorithms.
*/

#include <string>
#include <iostream>
#include <stdlib.h>
#include "sorting.h"
#include <ctime>
using namespace std;

/**
*swaps the values of the given indexes on the given array
*/
void swap(int *arr, int f, int l)
{
    int temp = arr[f];
    arr[f] = arr[l];
    arr[l] = temp;
}

/**
*creates two arrays around the selected pivot point
*/
void partition(int *arr, int f ,int l, int &pivotIndex, int &compCount, int &moveCount)
{
    // Precondition: theArray[first..last] is an array; first <= last.
    // Postcondition: Partitions theArray[first..last] such that:
    //   S1 = theArray[first..pivotIndex-1] < pivot
    //   theArray[pivotIndex] == pivot
    //   S2 = theArray[pivotIndex+1..last] >= pivot
    // place pivot in theArray[first]
    //choosePivot(theArray, first, last); (DEPRECATED)

    int pivot = arr[f]; // copy pivot
    // initially, everything but pivot is in unknown
    int lastS1 = f;           // index of last item in S1
    int firstUnknown = f + 1; // index of first item in unknown

    // move one item at a time until unknown region is empty
    for (  ; firstUnknown <= l; ++firstUnknown) {
      // Invariant: theArray[first+1..lastS1] < pivot
      //            theArray[lastS1+1..firstUnknown-1] >= pivot

      // move item from unknown to proper region
      if (arr[firstUnknown] < pivot) {  	// belongs to S1
          ++lastS1;
          swap(arr, firstUnknown, lastS1);
          //swap operation contains three moves
          moveCount+=3;
          compCount++;
      }	// else belongs to S2
    }
    // place pivot in proper position and mark its location
    pivotIndex = lastS1;
    //swap operation contains three moves
    swap(arr, f, lastS1);
    moveCount+=3;
}

/**
*executes the quick sort algorithm on the given array
*/
void quickSort(int *arr, int f ,int l, int &compCount, int &moveCount)
{
    // Precondition: theArray[first..last] is an array.
    // Postcondition: theArray[first..last] is sorted.
    //pivot index is selected as 0 as desired in the assignment
    int pivotIndex = 0;
    if (f < l) {
        // create the partition: S1, pivot, S2
        partition(arr, f, l, pivotIndex, compCount, moveCount);
        // sort regions S1 and S2
        quickSort(arr, f, pivotIndex-1, compCount, moveCount);
        quickSort(arr, pivotIndex+1, l, compCount, moveCount);
   }
}

/**
*executes the insertion sort algorithm on the given array
*/
void insertionSort(int *arr, int size, int &compCount, int &moveCount)
{
    //divide the array into two: sorted and unsortedon each iteration
    for (int unsorted = 1; unsorted < size; ++unsorted) {
        int nextItem = arr[unsorted];
        int loc = unsorted;
        for ( ;(loc > 0) && (arr[loc-1] > nextItem); --loc) {
           arr[loc] = arr[loc-1];
           compCount++;
           moveCount++;
        }
        arr[loc] = nextItem;
        moveCount++;
    }

}

/***
*executes the hyrid sort algorithm on the given array
*/
void hybridSort(int *arr, int size, int &compCount, int &moveCount)
{
    //initialize the minimum size to 10 as desired in the assignment
    int MINSIZE = 10;

    //execute insertion sort when array size is less than minimum size
    if(size < MINSIZE)
        insertionSort(arr, size, compCount, moveCount);
    else
    {
        //pivot index is selected as 0 as desired in the assignment
        int pivotIndex = 0;
        partition(arr, 0, size-1, pivotIndex, compCount, moveCount);
        // sort regions S1 and S2
        hybridSort(arr, pivotIndex, compCount, moveCount);
        //if the left region is not empty hybrid sort will be executed
        if(pivotIndex + 1 < size)
            hybridSort(&arr[pivotIndex+1], size - pivotIndex-1, compCount, moveCount);
    }
}
/**
*gets and prints the values of an array
*/
void printArray(int *arr, int size)
{
    for(int i = 0; i < size; i++) {
        cout<<arr[i]<<'\t';
    }
    cout<<'\n';
}

/*****
*creates 30 arrays of integers, each triple having the same random elements of size through 1500 to 15000
*quicksort, insertion sort and hybrid sort algortihms are tried on these arrays and their performance
*are printed
*/
void performanceAnalysis()
{
    //initialize arrays for size, move counts, comparison counts and elapsed times for each algorithm
    int *sizes = new int[10],*movecntQS = new int[10],*movecntIS = new int[10], *movecntHS = new int[10], *cmpcntQS = new int[10],
    *cmpcntIS = new int[10], *cmpcntHS = new int[10];
    double *timesQS = new double[10], *timesIS = new double[10], *timesHS = new double[10];
    for(int j = 1; j <= 10; j++) {
        int *arr1 = new int[1500*j], *arr2 = new int[1500*j], *arr3 = new int[1500*j];
        int c1 , c2, c3, m1, m2, m3 = 0;
        for(int i = 0; i < 1500*j; i++) {
            int temp = rand();
            arr1[i] = temp;
            arr2[i] = temp;
            arr3[i] = temp;
        }
        clock_t begin = clock();
        quickSort(arr1, 0,1500*j-1,c1,m1);
        clock_t end = clock();
        double elapsed_qs = double(end - begin) / CLOCKS_PER_SEC*100;
        timesQS[j-1] = elapsed_qs;
        movecntQS[j-1] = m1;
        cmpcntQS[j-1] = c1;

        begin = clock();
        insertionSort(arr2, 1500*j, c2, m2);
        end = clock();
        double elapsed_is = double(end - begin) / CLOCKS_PER_SEC*100;
        timesIS[j-1] = elapsed_is;
        movecntIS[j-1] = m2;
        cmpcntIS[j-1]= c2;

        begin = clock();
        hybridSort(arr3, 1500*j, c3, m3);
        end = clock();
        double elapsed_Hs = double(end - begin) / CLOCKS_PER_SEC * 100;
        timesHS[j-1] = elapsed_Hs;
        movecntHS[j-1] = m3;
        cmpcntHS[j-1] = c3;

        sizes[j-1] = j*1500;

        delete[] arr1; delete[] arr2; delete[] arr3;
    }
    cout<<"-------------------------------------------- \n";
    cout<<"part a: time analysis of Quick Sort \n";
    cout<<"array size"<<'\t'<<"Time elapsed(ms)"<<'\t'<<"compCount"<<'\t'<<"moveCount \n";
    for(int i = 1; i <=10; i++) {
        cout<<sizes[i-1]<<"\t \t"<<timesQS[i-1]<<"\t \t"<<cmpcntQS[i-1]<<"\t \t"<<movecntQS[i-1]<<'\n';
    }
    cout<<"-------------------------------------------- \n";
    cout<<"part b: time analysis of Insertion Sort \n";
    cout<<"array size"<<'\t'<<"Time elapsed(ms)"<<'\t'<<"compCount"<<'\t'<<"moveCount \n";
    for(int i = 1; i <= 10; i++) {
        cout<<sizes[i-1]<<"\t \t"<<timesIS[i-1]<<"\t \t"<<cmpcntIS[i-1]<<"\t \t"<<movecntIS[i-1]<<'\n';
    }
    cout<<"-------------------------------------------- \n";
    cout<<"part c: time analysis of Hybrid Sort \n";
    cout<<"array size"<<'\t'<<"Time elapsed(ms)"<<'\t'<<"compCount"<<'\t'<<"moveCount \n";
    for(int i = 1; i <= 10; i++) {
        cout<<sizes[i-1]<<"\t \t"<<timesHS[i-1]<<"\t \t"<<cmpcntHS[i-1]<<"\t \t"<<movecntHS[i-1]<<'\n';
    }

    delete[] sizes; delete[] movecntHS; delete[] movecntIS; delete[] movecntQS; delete[] cmpcntHS; delete[] cmpcntIS; delete[] cmpcntQS;
    delete[] timesQS; delete[] timesIS; delete[] timesHS;
}
