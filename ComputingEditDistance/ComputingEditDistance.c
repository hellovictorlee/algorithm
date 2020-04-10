// EditDistance
// Author: Shuai-Hsun Lee
// Date: JUNE 24 2016
// Language: C

#include <stdio.h>

int min(int, int, int);
int EditDistance(int* D, char*, char*, int, int);
void Display(int*, int, int);

int main()
{
    char A[] = "DISTANCE";
    char B[] = "EDITING";
    int n = sizeof(A) / sizeof(A[0]);
    int m = sizeof(B) / sizeof(B[0]);
    int D[m][n];
    
    printf("%s vs %s\n\n", A, B);
    
    int Distance = EditDistance((int*)D, A, B, n, m);
    
    Display((int*)D, n, m);
    
    printf("Minimun Distance = %d\n\n", Distance);
    
    return 0;
}


int min(int a, int b, int c)
{
    int temp;
    
    temp = a<b?a:b;
    temp = temp<c?temp:c;
    
    return temp;
}

int EditDistance(int* D, char* A, char* B, int n, int m)
{
    for(int i=0; i<n; i++)
        *(D+i) = i;
    for(int j=0; j<m; j++)
        *(D+n*j) = j;
    
    for(int j=1; j<m; j++)
        for(int i=1; i<n; i++)
        {
            int insertion = *(D+n*j+i-1) + 1;
            int deletion = *(D+n*(j-1)+i) + 1;
            int match = *(D+n*(j-1)+i-1);
            int mismatch = *(D+n*(j-1)+i-1) + 1;
            if(A[i-1] == B[j-1])
                *(D+n*j+i) = min(insertion, deletion, match);
            else
                *(D+n*j+i) = min(insertion, deletion, mismatch);
        }
    return *(D+n*m-1);
}

void Display(int* D, int n, int m)
{
    printf("Distance Table:\n");
    int i, j;
    for(i=0; i<m;i++)
    {
        for(j=0; j<n; j++)
            printf("%3d ",*(D+n*i+j));
        printf("\n");
    }
    printf("\n\n");
}