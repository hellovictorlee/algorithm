#include <stdlib.h>
#include "RandomizedQuickSort.h"

void swap(int *a, int*b){
    int temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
}

int* Partition3LS(int* A, int l, int r)
{
    int x = A[l];  // pivot
    int* m = (int*)malloc(2*sizeof(int));
    m[0] = l;
    m[1] = r;
    int i = l;
    
    while(i <= m[1])
        if(A[i] > x)
        {
            swap(A+m[0], A+i);
            m[0]++;
            i++;
        }
        else if(A[i] < x)
        {
            swap(A+m[1], A+i);
            m[1]--;
        }
        else
            i++;
    
    return m;
}

int* randomizedquicksortLS(int* A, int l, int r)
{
    if(l >= r)
        return A;
    int k = l + rand()%(r-l+1); // random number between l and r
    swap(A+l, A+k);
    
    int* m;
    m = Partition3LS(A, l, r);
    
    randomizedquicksortLS(A, l, m[0]-1);
    randomizedquicksortLS(A, m[1]+1, r);
    
    free(m);
    m = NULL;
    
    return A;
}

int* Partition3SL(int* A, int l, int r)
{
    int x = A[l];  // pivot
    int* m = (int*)malloc(2*sizeof(int));
    m[0] = l;
    m[1] = r;
    int i = l;
    
    while(i <= m[1])
        if(A[i] < x)
        {
            swap(A+m[0], A+i);
            m[0]++;
            i++;
        }
        else if(A[i] > x)
        {
            swap(A+m[1], A+i);
            m[1]--;
        }
        else
            i++;
    
    return m;
}

int* randomizedquicksortSL(int* A, int l, int r)
{
    if(l >= r)
        return A;
    int k = l + rand()%(r-l+1); // random number between l and r
    swap(A+l, A+k);
    
    int* m;
    m = Partition3SL(A, l, r);
    
    randomizedquicksortSL(A, l, m[0]-1);
    randomizedquicksortSL(A, m[1]+1, r);
    
    free(m);
    m = NULL;
    
    return A;
}