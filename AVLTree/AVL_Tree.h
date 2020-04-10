// C++
// AVL Tree
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

class Tree
{
protected:
    struct Node { Element element; int key, height = 0; struct Node *parent, *left, *right; };
    Node * root;
    static int size;
    Tree(const Tree & t) { size = 0; }
    Tree & operator=(const Tree & t) { return *this; }
public:
    Tree() : root(NULL) {}
    ~Tree() {}
    Node* Root() { return root; };
    bool is_empty() const { return size == 0; }
    int tree_count() const { return size; }
    Node* Tree_search(const int k);
    Node* Tree_minimum(Node* x);
    Node* Tree_maximum(Node* x);
    Node* Tree_successor(const int k);
    Node* Tree_predecessor(const int k);
    Node* Tree_insert(Element & elem, const int k);
    void Transplant(Node* u, Node* v);
    Node* Tree_delete(const int k);
    void print(const int k);
    Node* Tree_LeftDescendant(Node* n);
    Node* Tree_RightAncester(Node* n);
    Node* Tree_Next(Node* n);
    void Tree_RangeSearch(const int k1, const int k2);
};

class AVLTree : public Tree
{
public:
    void AVLTree_RotateLeft(Node* Y);
    void AVLTree_RotateRight(Node* X);
    void AVLTree_Rebalance(Node* n);
    int AVLTree_max(int a, int b) { return a > b ? a : b; }
    int AVLTree_Height(Node* n) { return n ? n->height : 0; }
    void AVLTree_AdjustHeight(Node* n) { n->height = 1 + AVLTree_max(AVLTree_Height(n->left), AVLTree_Height(n->right)); }
    void AVLTree_insert(Element & elem, const int k);
    void AVLTree_delete(const int k);
};
#endif