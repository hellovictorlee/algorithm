// C++
// Red-Black Tree
// Author: Lee, Shuai-Hsun
#ifndef TREE_H_
#define TREE_H_
#include <iostream>
#include <string>
using std::string;
using std::ostream;
class Data
{
private:
    string name;
    int value;
public:
    Data(const string & s = "no name", int v = 0);
    ~Data() {}
    const string Name() const { return name; }
    int Value() const { return value; }
    friend ostream & operator<<(ostream & os, Data data);
};

typedef Data Element;

class RBTree
{
private:
    enum Color { RED, BLACK };
    struct Node { Element element; int key; Color color = RED; struct Node *parent, *left, *right; };
    Node * Nil;
    Node * root;
    static int size;
    RBTree(const RBTree & t) { size = 0; }
    RBTree & operator=(const RBTree & t) { return *this; }
public:
    RBTree() { Nil = new Node; Nil->parent = Nil->left = Nil->right = NULL;
        Nil->color = BLACK; Nil->key = 0; root = Nil; }
    ~RBTree() {}
    Node* Root() { return root; };
    bool is_empty() const { return size == 0; }
    int tree_count() const { return size; }
    Node* Tree_search(const int k);
    Node* Tree_minimum(Node* x);
    Node* Tree_maximum(Node* x);
    Node* Tree_successor(const int k);
    Node* Tree_predecessor(const int k);
    Node* Tree_insert(Element & elem, const int k);
    void print(const int k);
    Node* Tree_LeftDescendant(Node* n);
    Node* Tree_RightAncester(Node* n);
    Node* Tree_Next(Node* n);
    void Tree_RangeSearch(const int k1, const int k2);
    
    void RBTree_RotateLeft(Node* Y);
    void RBTree_RotateRight(Node* X);
    void RBTree_insert_finxup(Node* z);
    void RBTree_insert(Element & elem, const int k);
    void RBTree_Transplant(Node* u, Node* v);
    void RBTree_delete_fixup(Node* z);
    void RBTree_delete(const int k);
};
#endif