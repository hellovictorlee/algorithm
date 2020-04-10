#include <stdlib.h>
#include "mergesort.h"

void swap(int *a, int*b)
{
    int temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
}

int larger(int a, int b)
{
    return a > b;
}

int smaller(int a, int b)
{
    return a < b;
}

int* Merge(int* B, int* C, int x, int y, int (*compare)(int, int))
{
    int i, j, k;
    i = j = k = 0;
    int A[x];
    
    for(int i=0; i<x; i++)
        A[i] = B[i];
    
    while(i<x && j<y)
    {
        if(compare(A[i], C[j]))
            B[k++] = A[i++];
        else
            B[k++] = C[j++];
    }
    
    while(i < x)
        B[k++] = A[i++];
    
    while(j < y)
        B[k++] = C[j++];
    
    return B;
}

int* MergeSort(int* A, int n, int (*compare)(int, int))
{
    if(n == 1)
        return A;
    int m;
    int *B, *C;
    m = n / 2;
    
    B = MergeSort(A, m, compare);
    C = MergeSort(A + m, n - m, compare);
    
    A = Merge(B, C, m, n-m, compare);
    
    return A;
}