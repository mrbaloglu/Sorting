#ifndef SORTING_H_
#define SORTING_H_

void swap(int *arr, int f, int l);
void partition(int *arr, int f ,int l, int &pivotIndex, int &compCount, int &moveCount);
void quickSort(int *arr, int f ,int l, int &compCount, int &moveCount);
void insertionSort(int *arr, int size, int &compCount, int &moveCount);
void hybridSort(int *arr, int size, int &compCount, int &moveCount);
void printArray(int *arr, int size);
void performanceAnalysis();
#endif //SORTING_H_
