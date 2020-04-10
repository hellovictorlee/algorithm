// Knapsack Problem without Repetition
// author: Shuai-Hsun Lee
// Date: June 23 2016
// programming tool: C

#include <stdio.h>
#define LIMIT 10

typedef struct{
    int weight;
    int price;
}FRUIT;

int knapsack(FRUIT*, int*, int);
void Display(int*, int);

int main()
{
    FRUIT Fruits[] = {
        {0, 0},
        {6, 30},
        {3, 14},
        {4, 16},
        {2, 9}};
    const int length = sizeof(Fruits)/sizeof(Fruits[0]);
    int values[length][LIMIT+1] = {0};
    
    int M = knapsack(Fruits, (int*)values, length);
    
    Display((int*)values, length);
    
    printf("Max Value = %d\n\n", M);
    
    return 0;
}


int knapsack(FRUIT* Fruits, int* values, int length)
{
    for(int j=0; j<length; j++)
        *(values+j*(LIMIT+1)) = 0;
    for(int w=0; w<=LIMIT; w++)
        *(values+w) = 0;
    
    for(int j=1; j<length; j++)
        for(int w=1; w<=LIMIT; w++)
        {
            *(values+(LIMIT+1)*j+w) = *(values+(LIMIT+1)*(j-1)+w);  // value(w,j) = value(w,j-1)
            if(Fruits[j].weight <= w)
            {
                int newValue = *(values+(LIMIT+1)*(j-1)+(w-Fruits[j].weight)) + Fruits[j].price;  // newValue = value(w-wi,i-1) + vi;
                if(*(values+(LIMIT+1)*j+w) < newValue)  // if(newValue > value(w,i))
                    *(values+(LIMIT+1)*j+w) = newValue;  // value(w,i) = newValue
            }
        }
    return *(values+(LIMIT+1)*(length)-1);
}

void Display(int* values, int length)
{
    for(int j=0; j<length; j++)
    {
        for(int w=0; w<=LIMIT; w++)
            printf("%2d ",*(values+(LIMIT+1)*j+w));
        printf("\n");
    }
    printf("\n\n");
}