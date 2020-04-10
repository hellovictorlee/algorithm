#include <stdio.h>
#include <stdlib.h>
#include "HeapSort.h"


int main()
{
    int length, SIZE;
    length = SIZE = 5;
    
    int number1[] = {3, 5, 1, 6, 9};
    int* A1 = Heapsort(number1, length, SIZE, LS);
    printf("大的在前 ");
    int i;
    for(i = 0; i < 5; i++) {
        printf("%d ", A1[i]);
    }
    putchar('\n');
    
    int number2[] = {3, 5, 1, 6, 9};
    int* A2 = Heapsort(number2, length, SIZE, SL);
    printf("小的在前 ");
    for(i = 0; i < 5; i++) {
        printf("%d ", A2[i]);
    }
    putchar('\n');
    
    return 0;
}