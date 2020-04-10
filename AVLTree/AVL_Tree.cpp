// C++
// AVL Tree
// Author: Lee, Shuai-Hsun
#include <iostream>
#include <vector>
#include "AVL_Tree.h"

int Tree::size = 0;

Data::Data(const string & s, int v) : name(s), value(v) {}

Tree::Node* Tree::Tree_search(const int k)
{
    Node* x = root;
    while(x != NULL && k != x->key)
    {
        if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

Tree::Node* Tree::Tree_minimum(Node* x)
{
    while(x->left != NULL)
        x = x->left;
    return x;
}

Tree::Node* Tree::Tree_maximum(Node* x)
{
    while(x->right != NULL)
        x = x->right;
    return x;
}

Tree::Node* Tree::Tree_successor(const int k)
{
    Node* x = Tree_search(k);
    if(!x)
        return NULL;
    if(x->right != NULL)
        return Tree_minimum(x);
    Node* y = x->parent;
    while(y != NULL && x== y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

Tree::Node* Tree::Tree_predecessor(const int k)
{
    Node* x = Tree_search(k);
    if(!x)
        return NULL;
    if(x->left != NULL)
        return Tree_maximum(x);
    Node* y = x->parent;
    while(y != NULL && x== y->left)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

Tree::Node* Tree::Tree_insert(Element & elem, const int k)
{
    Node* add = new Node;
    add->left = NULL;
    add->right = NULL;
    add->element = elem;
    add->key = k;
    Node* y = NULL;
    Node* x = root;
    while(x != NULL)
    {
        y = x;          // record the insert location
        if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    add->parent = y;
    if(y == NULL)       // tree was empty
        root = add;
    else if(k < y->key)
        y->left = add;
    else
        y->right = add;
    size++;
    return add;
}

void Tree::Transplant(Tree::Node *u, Tree::Node *v)
{
    if(u->parent == NULL)
        root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if(v != NULL)
        v->parent = u->parent;
}

Tree::Node* Tree::Tree_delete(const int k)
{
    Node* z = Tree_search(k);
    if(z == NULL)
        return NULL;
    Node* temp;
    if(z->left == NULL)
    {
        temp = z->parent;
        Transplant(z, z->right);
    }
    else if(z->right == NULL)
    {
        temp = z->parent;
        Transplant(z, z->left);
    }
    else
    {
        temp = z->right;
        Node* y = Tree_minimum(z->right);
        if(y->parent != z)
        {
            temp = y->parent;
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    delete z;
    z = NULL;
    return temp;
}

ostream & operator<<(ostream & os, Data data)
{
    os << data.Name();
    return os;
}

void Tree::print(const int k)
{
    using std::cout;
    using std::endl;
    Node* x = Tree_search(k);
    if(!x)
        return;
    
    if(x->parent == NULL)
        cout << "         NULL, 0" << endl;
    else
        cout << "         " << x->parent->element << ", " << x->parent->height << endl;
    if(x == NULL)
        cout << "         NULL, 0" << endl;
    else
        cout << "         " << x->element << ", " << x->height << endl;
    if(x->left == NULL && x->right == NULL)
        cout << "NULL, 0          NULL, 0" << endl;
    else if(x->left == NULL && x->right != NULL)
        cout << "NULL, 0          " << x->right->element << ", " << x->right->height << endl;
    else if(x->left != NULL && x->right == NULL)
        cout << x->left->element << ", " << x->left->height << "          NULL, 0" << endl;
    else
        cout << x->left->element << ", " << x->left->height << "          " << x->right->element << ", " << x->right->height << endl;;
}

Tree::Node* Tree::Tree_LeftDescendant(Tree::Node* n)
{
    if(n->left == NULL)
        return n;
    else
        return Tree_LeftDescendant(n->left);
}

Tree::Node* Tree::Tree_RightAncester(Tree::Node* n)
{
    if(n->parent != NULL)
    {
        if(n->key < n->parent->key)
            return n->parent;
        else
            return Tree_RightAncester(n->parent);
    }
    return NULL;
}

Tree::Node* Tree::Tree_Next(Tree::Node* n)  // Find next larger than N
{
    if(n == NULL)
        return n;
    if(n->right != NULL)
        return Tree_LeftDescendant(n->right);
    else
        return Tree_RightAncester(n);
}

void Tree::Tree_RangeSearch(const int k1, const int k2)  // x <= range < y
{
    Node* n = NULL;
    int temp = k1;
    while(n == NULL && temp <= k2)
    {
        n = Tree_search(temp);
        temp++;
    }
    if(n != NULL)
    {
        using std::vector;
        vector<Node*> vec;
        while(n->key <= k2)
        {
            if(n->key >= k1)
                vec.push_back(n);
            n = Tree_Next(n);
            if(n == NULL)
                break;
        }
        // print all Key //
        vector<Node*>::iterator v = vec.begin();
        if( v == vec.end())
        {
            std::cout << "not found\n";
            return;
        }
        while( v != vec.end()) {
            std::cout << (*v)->element.Name() << std::endl;
            v++;
        }
    }
    else
        std::cout << "not found\n";
}

void AVLTree::AVLTree_RotateLeft(AVLTree::Tree::Node* Y)
{
    Node* P = Y->parent;
    Node* X = Y->right;
    Node* B = X->left;
    if(P == NULL)
        root = X;  // Root reset
    else
    {
        if(P->key > X->key)
            P->left=X;
        else
            P->right=X;
    }
    X->parent = P;
    Y->parent = X;
    X->left = Y;
    if(B != NULL)
        B->parent = Y;
    Y->right = B;
}

void AVLTree::AVLTree_RotateRight(AVLTree::Tree::Node* X)
{
    Node* P = X->parent;
    Node* Y = X->left;
    Node* B = Y->right;
    if(P == NULL)
        root = Y;  // Root reset
    else
    {
        if(P->key > Y->key)
            P->left=Y;
        else
            P->right=Y;
    }
    Y->parent = P;
    X->parent = Y;
    Y->right = X;
    if(B != NULL)
        B->parent = X;
    X->left = B;
}

void AVLTree::AVLTree_Rebalance(Node* n)
{
    Node* m;
    if(AVLTree_Height(n->left) > AVLTree_Height(n->right)+1)
    {
        m = n->left;
        if(AVLTree_Height(m->right) > AVLTree_Height(m->left))
        {
            AVLTree_RotateLeft(m);
            AVLTree_AdjustHeight(m);
        }
        AVLTree_RotateRight(n);
    }
    if(AVLTree_Height(n->right) > AVLTree_Height(n->left)+1)
    {
        m = n->right;
        if(AVLTree_Height(m->left) > AVLTree_Height(m->left))
        {
            AVLTree_RotateRight(m);
            AVLTree_AdjustHeight(m);
        }
        AVLTree_RotateLeft(n);
    }
    AVLTree_AdjustHeight(n);  // AdjustHeight the Parent of N
    
    Node* p = n->parent;
    if(p)
        AVLTree_Rebalance(p);  // update the Parent of N
}

void AVLTree::AVLTree_insert(Element & elem, const int k)
{
    Tree_insert(elem, k);
    Node* n = Tree_search(k);
    AVLTree_Rebalance(n);
}

void AVLTree::AVLTree_delete(const int k)
{
    Node* n = Tree_delete(k);
    if(n != NULL)
        AVLTree_Rebalance(n);
}