#include <stdio.h>
#include "RandomizedQuickSort.h"

int main(void) {
    int number1[] = {3, 5, 1, 6, 9, 9 , 1 , 2};
    int* A1 = randomizedquicksortLS(number1, 0, 7);
    printf("大的在前 ");
    int i;
    for(i = 0; i < 8; i++) {
        printf("%d ", A1[i]);
    }
    putchar('\n');
    
    int number2[] = {3, 5, 1, 6, 9, 9 , 1 , 2};
    int* A2 = randomizedquicksortSL(number2, 0, 7);
    printf("小的在前 ");
    for(i = 0; i < 8; i++) {
        printf("%d ", A2[i]);
    }
    putchar('\n');
    
    return 0;
}