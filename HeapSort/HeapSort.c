#include "HeapSort.h"


int LS(int a, int b)
{
    return a > b;
}

int SL(int a, int b)
{
    return a < b;
}

void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int Parent(int i)
{
    return (i+1)/2-1;  // origin: i/2 =>  i=i+1 & return -1
}

int LeftChild(int i)
{
    return 2*(i+1)-1;  // orign: 2*i =>  i=i+1 & return -1
}

int RightChild(int i)
{
    return 2*(i+1);  // origin: 2*i+1 =>  i=i+1 & return -1
}

void SiftDown(int* tree, int i, int SIZE, int (*compare)(int, int))
{
    int P, L, R;
    P = i;  // P is a parent of L and R
    
    L = LeftChild(i);  // be careful
    if(L<SIZE && compare(tree[L],tree[P]))  // compare L to P
        P = L;  // P turn into L
    
    R = RightChild(i);  // be careful
    if(R<SIZE && compare(tree[R],tree[P]))  // compare R to P(maybe original L)
        P = R;  // P(maybe original L) turn into R
    
    if(i != P)  // check if need to swap or not
    {
        swap(tree+i, tree+P);
        SiftDown(tree, P, SIZE, compare);
    }
}

void BuildHeap(int* tree, int SIZE, int (*compare)(int, int))
{
    for(int i=SIZE/2-1; i>-1; i--)
        SiftDown(tree, i, SIZE, compare);
}

int* Heapsort(int* tree, int length, int SIZE, int (*compare)(int, int))
{
    BuildHeap(tree, SIZE, compare);  // Build a tree heap than GetMax
    
    for(int j=0; j<length-1; j++)
    {
        swap(tree, tree+(SIZE-1));  // GetMax than put it to the back
        SIZE--;
        SiftDown(tree, 0, SIZE, compare);
    }
    
    return tree;
}