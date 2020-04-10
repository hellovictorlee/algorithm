#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"


int main(void)
{
    int number1[] = {3, 5, 1, 6, 9};
    int* A1;
    A1 = MergeSort(number1, 5, larger);
    printf("大的在前 ");
    int i;
    for(i = 0; i < 5; i++)
        printf("%d ", A1[i]);
    putchar('\n');
    
    int number2[] = {3, 5, 1, 6, 9};
    int* A2;
    A2 = MergeSort(number2, 5, smaller);
    printf("小的在前 ");
    for(i = 0; i < 5; i++)
        printf("%d ", A2[i]);
    putchar('\n');
    
    return 0;
}