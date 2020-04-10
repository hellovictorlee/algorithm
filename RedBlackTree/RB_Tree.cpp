// C++
// Red-Black Tree
// Author: Lee, Shuai-Hsun
#include <iostream>
#include <vector>
#include "RB_Tree.h"

int RBTree::size = 0;

Data::Data(const string & s, int v) : name(s), value(v) {}

RBTree::Node* RBTree::Tree_search(const int k)
{
    Node* x = root;
    while(x != Nil && k != x->key)
    {
        if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

RBTree::Node* RBTree::Tree_minimum(Node* x)
{
    while(x->left != Nil)
        x = x->left;
    return x;
}

RBTree::Node* RBTree::Tree_maximum(Node* x)
{
    while(x->right != Nil)
        x = x->right;
    return x;
}

RBTree::Node* RBTree::Tree_successor(const int k)
{
    Node* x = Tree_search(k);
    if(!x)
        return Nil;
    if(x->right != Nil)
        return Tree_minimum(x);
    Node* y = x->parent;
    while(y != Nil && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

RBTree::Node* RBTree::Tree_predecessor(const int k)
{
    Node* x = Tree_search(k);
    if(!x)
        return Nil;
    if(x->left != Nil)
        return Tree_maximum(x);
    Node* y = x->parent;
    while(y != Nil && x== y->left)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

RBTree::Node* RBTree::Tree_insert(Element & elem, const int k)
{
    Node* add = new Node;
    add->left = Nil;
    add->right = Nil;
    add->element = elem;
    add->key = k;
    Node* y = Nil;
    Node* x = root;
    while(x != Nil)
    {
        y = x;          // record the insert location
        if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    add->parent = y;
    if(y == Nil)       // tree was empty
        root = add;
    else if(k < y->key)
        y->left = add;
    else
        y->right = add;
    size++;
    return add;
}

ostream & operator<<(ostream & os, Data data)
{
    os << data.Name();
    return os;
}

void RBTree::print(const int k)
{
    using std::cout;
    using std::endl;
    Node* x = Tree_search(k);
    if(x == Nil)
        return;
    
    if(x->parent == Nil)
        cout << "         Nil, 1" << endl;
    else
        cout << "         " << x->parent->element << ", " << x->parent->color << endl;
    if(x == Nil)
        cout << "         Nil, 1" << endl;
    else
        cout << "         " << x->element << ", " << x->color << endl;
    if(x->left == Nil && x->right == Nil)
        cout << "Nil, 1          Nil, 1" << endl;
    else if(x->left == Nil && x->right != Nil)
        cout << "Nil, 1          " << x->right->element << ", " << x->right->color << endl;
    else if(x->left != Nil && x->right == Nil)
        cout << x->left->element << ", " << x->left->color << "          Nil, 1" << endl;
    else
        cout << x->left->element << ", " << x->left->color << "          " << x->right->element << ", " << x->right->color << endl;;
}

RBTree::Node* RBTree::Tree_LeftDescendant(RBTree::Node* n)
{
    if(n->left == Nil)
        return n;
    else
        return Tree_LeftDescendant(n->left);
}

RBTree::Node* RBTree::Tree_RightAncester(RBTree::Node* n)
{
    if(n->parent != Nil)
    {
        if(n->key < n->parent->key)
            return n->parent;
        else
            return Tree_RightAncester(n->parent);
    }
    return Nil;
}

RBTree::Node* RBTree::Tree_Next(RBTree::Node* n)  // Find next larger than N
{
    if(n == Nil)
        return n;
    if(n->right != Nil)
        return Tree_LeftDescendant(n->right);
    else
        return Tree_RightAncester(n);
}

void RBTree::Tree_RangeSearch(const int k1, const int k2)  // x <= range < y
{
    Node* n = Nil;
    int temp = k1;
    while(n == Nil && temp <= k2)
    {
        n = Tree_search(temp);
        temp++;
    }
    if(n != Nil)
    {
        using std::vector;
        vector<Node*> vec;
        while(n->key <= k2)
        {
            if(n->key >= k1)
                vec.push_back(n);
            n = Tree_Next(n);
            if(n == Nil)
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

void RBTree::RBTree_RotateLeft(RBTree::Node* Y)
{
    Node* P = Y->parent;
    Node* X = Y->right;
    Node* B = X->left;
    if(P == Nil)
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
    if(B != Nil)
        B->parent = Y;
    Y->right = B;
}

void RBTree::RBTree_RotateRight(RBTree::Node* X)
{
    Node* P = X->parent;
    Node* Y = X->left;
    Node* B = Y->right;
    if(P == Nil)
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
    if(B != Nil)
        B->parent = X;
    X->left = B;
}

void RBTree::RBTree_insert_finxup(RBTree::Node * z)
{
    Node * y;
    while(z->parent->color == RED)
    {
        if(z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if(y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if(z == z->parent->right)
                {
                    z = z->parent;
                    RBTree_RotateLeft(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RBTree_RotateRight(z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if(y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if(z == z->parent->left)
                {
                    z = z->parent;
                    RBTree_RotateRight(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RBTree_RotateLeft(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::RBTree_insert(Element & elem, const int k)
{
    RBTree_insert_finxup(Tree_insert(elem, k));
}

void RBTree::RBTree_Transplant(RBTree::Node *u, RBTree::Node *v)
{
    if(u->parent == Nil)
        root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

void RBTree::RBTree_delete_fixup(RBTree::Node *x)
{
    Node* w;
    while(x != root && x->color == BLACK)
    {
        if(x == x->parent->left)
        {
            w = x->parent->right;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RBTree_RotateLeft(x->parent);
                continue;
            }
            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RBTree_RotateRight(w);
                    w = x->parent;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                RBTree_RotateLeft(x->parent);
                x = root;
            }
        }
        else
        {
            w = x->parent->left;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RBTree_RotateRight(x->parent);
                continue;
            }
            if(w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    RBTree_RotateLeft(w);
                    w = x->parent;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RBTree_RotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RBTree::RBTree_delete(const int k)
{
    Node* z = Tree_search(k);
    Node* y = z;
    Color y_original_color = y->color;
    Node* x;
    if(z->left == Nil)
    {
        x = z->right;
        RBTree_Transplant(z, z->right);
    }
    else if(z->right == Nil)
    {
        x = z->left;
        RBTree_Transplant(z, z->left);
    }
    else
    {
        Node* y = Tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == z)
            x->parent = y;
        else
        {
            RBTree_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RBTree_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    z = NULL;
    if(y_original_color == BLACK)
        RBTree_delete_fixup(x);
}