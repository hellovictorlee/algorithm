// C
// Splay Tree
// Author: Lee, Shuai-Hsun
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int key;
    long long sum;
    struct node* left;
    struct node* right;
    struct node* parent;
}NODE;


void Display(NODE* N)
{
    printf("\n");
    
    if(N->parent)
        printf("        %d\n", N->parent->key);
    else
        printf("        NULL\n");
    printf("        %d\n", N->key);
    if(N->left)
        printf("%d", N->left->key);
    else
        printf("NULL");
    if(N->right)
        printf("              %d\n", N->right->key);
    else
        printf("              NULL\n");
}

void update(NODE* v) {
    if (v == NULL) return;
    v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
    if (v->left != NULL) {
        v->left->parent = v;
    }
    if (v->right != NULL) {
        v->right->parent = v;
    }
}

void small_rotation(NODE* v) {
    NODE* parent = v->parent;
    if (parent == NULL) {
        return;
    }
    NODE* grandparent = v->parent->parent;
    if (parent->left == v) {
        NODE* m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        NODE* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        } else {
            grandparent->right = v;
        }
    }
}

void big_rotation(NODE* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

void splay(NODE** root, NODE* v) {
    if (v == NULL) return;
    while (v->parent != NULL) {
        if (v->parent->parent == NULL) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    *root = v;
}

NODE* find(NODE** R, int key) {
    NODE* v = *R;
    NODE* last = *R;
    NODE* next = NULL;
    while (v != NULL) {
        if (v->key >= key && (next == NULL || v->key < next->key)) {
            next = v;
        }
        last = v;
        if (v->key == key) {
            break;
        }
        if (v->key < key) {
            v = v->right;
        } else {
            v = v->left;
        }
    }
    splay(R, last);
    return next;
}

void split(NODE** root_ptr, int key, NODE** left, NODE** right) {
    *right = find(root_ptr, key);
    splay(root_ptr, *right);
    if (*right == NULL) {
        *left = *root_ptr;
        return;
    }
    *left = (*right)->left;
    (*right)->left = NULL;
    if (*left != NULL) {
        (*left)->parent = NULL;
    }
    update(*left);
    update(*right);
}

NODE* merge(NODE* left, NODE* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    NODE* min_right = right;
    while (min_right->left != NULL) {
        min_right = min_right->left;
    }
    splay(&right, min_right);
    right->left = left;
    left->parent = right;
    update(right);
    return right;
}

NODE* root;
NODE** root_ptr = &root;

void insert(int x) {
    if(*root_ptr == NULL)
    {
        NODE* new_vertex = (NODE*)malloc(sizeof(NODE));
        new_vertex->key = x;
        new_vertex->sum = x;
        new_vertex->parent = NULL;
        new_vertex->left = NULL;
        new_vertex->right = NULL;
        *root_ptr = new_vertex;
        return;
    }
    NODE* left = NULL;
    NODE* right = NULL;
    NODE* new_vertex = NULL;
    split(root_ptr, x, &left, &right);
    if (right == NULL || right->key != x) {
        new_vertex = (NODE*)malloc(sizeof(NODE));
        new_vertex->key = x;
        new_vertex->sum = x;
        new_vertex->parent = NULL;
        new_vertex->left = NULL;
        new_vertex->right = NULL;
    }
    *root_ptr = merge(merge(left, new_vertex), right);
}

void delete(int x){
    if(find(root_ptr, x) == NULL) return;
    if(find(root_ptr, x)->key != x) return;
    NODE* left = NULL;
    NODE* right = NULL;
    split(root_ptr, x, &left, &right);
    if(right->right != NULL)
        right->right->parent = NULL;
    NODE* temp = right;
    right = right->right;
    free(temp);
    temp = NULL;
    *root_ptr = merge(left, right);
}

bool Boolfind(int x) {
    if(*root_ptr == NULL) return false;
    if(find(root_ptr, x) == NULL) return false;
    if(find(root_ptr, x)->key != x) return false;
    splay(root_ptr, find(root_ptr, x));
    return true;
}

long long sum(int from, int to) {
    NODE* left = NULL;
    NODE* middle = NULL;
    NODE* right = NULL;
    split(root_ptr, from, &left, &middle);
    split(&middle, to + 1, &middle, &right);
    long long ans = 0;
    if(middle != NULL)
        ans = (middle)->sum;
    else
        ans = 0;
    
    NODE* R= merge(middle, right);
    R = merge(left, R);
    *root_ptr = R;
    
    return ans;
}

const int MODULO = 1000000001;

int main(){
    root = NULL;
    int n;
    scanf("%d", &n);
    int last_sum_result = 0;
    for (int i = 0; i < n; i++) {
        char buffer[10];
        scanf("%s", buffer);
        char type = buffer[0];
        switch (type) {
            case '+' : {
                int x;
                scanf("%d", &x);
                insert((x + last_sum_result) % MODULO);
            } break;
            case '-' : {
                int x;
                scanf("%d", &x);
                delete((x + last_sum_result) % MODULO);
            } break;
            case '?' : {
                int x;
                scanf("%d", &x);
                printf(Boolfind((x + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
            } break;
            case 's' : {
                int l, r;
                scanf("%d %d", &l, &r);
                long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
                printf("%lld\n", res);
                last_sum_result = (int)(res % MODULO);
            }
        }
    }
    return 0;
}
