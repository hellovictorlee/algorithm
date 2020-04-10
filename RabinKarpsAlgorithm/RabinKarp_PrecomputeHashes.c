// C
// Rabin-Karp Algorithm
// Author: Lee, Shuai-Hsun
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


typedef struct list
{
    int position;
    struct list* next;
}LIST;
LIST *head, *tail;

void init();
void Append(int);
unsigned long PolyHash(char*, unsigned long, unsigned long);
unsigned long* PrecomputeHashes(char*, unsigned long, unsigned long, unsigned long, unsigned long);
void RabinKarp(char*, char*);
void Release();


int main()
{
    init();
    
    char *T, *P;
    char STR1[] = "testTesttesT";
    char STR2[] = "Test";
    T = STR1;
    P = STR2;
    
    //char S1[] = "sabddabdabd";
    //char S2[] = "ab";
    
    
    RabinKarp(T, P);
    
    LIST* temp = head;
    while(temp)
    {
        printf("i = %d\n", temp->position);
        temp = temp->next;
    }
    
    Release();
    
    return 0;
}


void init()
{
    head = tail = NULL;
}

void Append(int i)
{
    LIST* p = (LIST*)malloc(sizeof(LIST));
    if(p)
    {
        p->position = i;
        p->next = NULL;
        if(head)
        {
            tail->next = p;  // last list point to p
            tail = p;
        }
        else
            head = tail = p;
    }
    else
        printf("no enough space\n");
}

unsigned long PolyHash(char* S, unsigned long p, unsigned long x)
{
    unsigned long hash = 0;
    unsigned long Length = strlen(S);
    unsigned long i;
    
    // (S[1]+(S[2]mod p)x)mod p = (S[1]+(S[2]x)mod p)mod p = (S[1]+S[2]x)mod p //
    for(i=0; i<Length; i++)
        hash = (hash*x + toascii(S[Length-1-i])) % p;
    return hash;
}

unsigned long* PrecomputeHashes(char* T, unsigned long Length_T, unsigned long Length_P, unsigned long p, unsigned long x)
{
    unsigned long i;
    
    unsigned long* H = (unsigned long*)malloc((Length_T-Length_P+1)*sizeof(unsigned long));
    char S[Length_P + 1];
    for(i=0; i<Length_P+1; i++)
    {
        if(i<Length_P)
            S[i] = T[i+Length_T-Length_P];
        else
            S[i] = '\0';
    }
    H[Length_T-Length_P] = PolyHash(S, p, x);
    unsigned long y = 1;
    for(i=1; i<Length_P+1; i++)
        y = (y*x) % p;
    for(i=0; i<Length_T-Length_P; i++)
        H[Length_T-Length_P-1-i] = (x*H[Length_T-Length_P-i]+T[Length_T-Length_P-1-i]-y*T[Length_T-1-i])%p;
    
    return H;
}

void RabinKarp(char* T, char* P)
{
    unsigned long p = 1073676287;
    unsigned long x = (random() % (p-1))+1;  // range:1~p-1
    unsigned long pHash = PolyHash(P, p, x);
    
    unsigned long Length_T = strlen(T);
    unsigned long Length_P = strlen(P);
    
    unsigned long* H = PrecomputeHashes(T, Length_T, Length_P, p, x);
    
    char S[Length_P+1];
    for(int i=0; i<Length_T-Length_P+1; i++)
    {
        for(int j=0; j<Length_P+1; j++)  // create a string to compare
        {
            if(j<Length_P)
                S[j] = T[i+j];
            else
                S[j] = '\0';  // In string.h, '\0' is necessary to strcmp, but it's not to strncmp.
        }
        
        if(pHash != H[i])
            continue;
        if(strcmp(S, P) == 0)
            Append(i);
    }
}

void Release()
{
    LIST* p;
    
    tail = NULL;
    while(head)
    {
        p = head;
        head = head->next;
        free(p);
    }
}