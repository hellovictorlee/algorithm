int LS(int ,int);
int SL(int ,int);
void swap(int*, int*);
int Parent(int);
int LeftChild(int);
int RightChild(int);
void SiftDown(int*, int, int, int (*compare)(int, int));
void BuildHeap(int*, int, int (*compare)(int, int));
int* Heapsort(int*, int, int, int (*compare)(int, int));