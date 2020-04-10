// C++
// B-Tree
// Author: Lee, Shuai-Hsun
#include <iostream>
#include <vector>


// class Node can be used for class BTree.
class Node
{
private:
    int t;        // Size definition which define the size range for every node
    int keysNum;  // Number of keys in the node
    bool leaf;    // Check if the node is leaf or not
    int* keys;    // Store all keys in the node
    Node** child; // Store all children's address
    
    // The protection mechanism that the object can't be copied
    // Constructor and operator= are designed to private member instead of public member
    // so that any action about copying the object is not available.
    Node(const Node & t) : keysNum(0) {}
    Node & operator=(const Node & t) { return *this; }
public:
    Node(int _t) : t(_t) { keysNum = 0; leaf = true; keys = new int[2*_t-2]; child = new Node*[2*_t-1]; }
    ~Node() {}
    
    // class Node can be used for class BTree.
    // We design node class first and Tree class can utilize node class create every object as Tree's each node.
    friend class BTree;
};


// In this class, we implement techniques to control every nodes.
class BTree
{
    struct Address { Node* node; int i; }; // This struct is used to store exact key's location.
private:
    Node* root;                // root node whose number of key can be less than t-1 is special
    int t;                     // capacity owning same name to class Node t is used to define every node size range which is between t-1 to 2*t-1
    std::vector<Address> vect; // vect which can trace every node it passed.
                               // In the other words, we can use vect to trace the node's parent so that we can implement Delete function's Case_Three function.
public:
    BTree(int _t) : root(NULL), t(_t) {}
    ~BTree() {}
    
    // Output every keys in order
    void Traverse(Node* x);
    
    // Split_child and Insert_nonfull is used to implement Insert function.
    void Split_child(Node* x, int i);
    void Insert_nonfull(Node* x, int k);
    void Insert(int k);
    
    // Three cases are used to Delete in different conditions.
    // Search function is the first step finding the key which we want to delete.
    Node* Root() { return root; }
    Address Search(Node* x, int k);
    void Merge(Node* x, int i);
    void Move_Down(Node* x, int i);
    void Add_Key(Node* x, int i);
    void Merge_Delete(Node* x, int i);
    Address Nonleaf_Move_Down(Node* x, int i);
    void Nonleaf_Remove(Node* x, int i);
    void Leaf_Remove(Node* x, int i);
    void Delete(int k);
};

// The traverse is "In Order Traversal".
void BTree::Traverse(Node* x)
{
    if(!x->leaf)
    {
        Traverse(x->child[0]);
        for(int i=0; i<x->keysNum; i++)
        {
            std::cout << x->keys[i] << " ";
            Traverse(x->child[i+1]);
        }
    }
    else
    {
        for(int i=0; i<x->keysNum; i++)
            std::cout << x->keys[i] << " ";
    }
}

/*
void BTree::Traverse(Node* x)
{
    std::cout << " - ";
    if(!x->leaf)
    {
        Traverse(x->child[0]);
        for(int i=0; i<x->keysNum; i++)
        {
            std::cout << x->keys[i] << " ";
            Traverse(x->child[i+1]);
        }
    }
    else
    {
        std::cout << " \\ ";
        for(int i=0; i<x->keysNum; i++)
            std::cout << x->keys[i] << " ";
        std::cout << "/ ";
    }
}
*/

void BTree::Split_child(Node* x, int i)
{
    // z and y are x's children.
    // Create a new node z copying the right half keys and children address from y.
    // The middle key is put in the x which is the parent of z and y.
    Node* z = new Node(t);
    Node* y = x->child[i];
    z->leaf = y->leaf;
    z->keysNum = t-1;
    for(int j=0; j<t-1; j++)
        z->keys[j] = y->keys[j+t];
    
    // If y is not leaf, z has to copy the right half children and vice versa.
    if(!y->leaf)
        for(int j=0; j<t; j++)
            z->child[j] = y->child[j+t];
    y->keysNum = t-1;
    
    // Because we insert the middle key into x, all the x's child element after the middle key have to move a space.
    for(int j=x->keysNum; j>=i+1 ; j--)
        x->child[j+1] = x->child[j];
    x->child[i+1] = z;
    
    // Because we insert the middle key into x, all the x's keys element after the middle key have to move a space.
    for(int j=x->keysNum-1; j>=i; j--)
        x->keys[j+1] = x->keys[j];
    x->keys[i] = y->keys[t-1];
    (x->keysNum)++;
}

void BTree::Insert_nonfull(Node* x, int k)
{
    // B-Tree always insert key to the node which is leaf.
    // B-Tree grows deep from root.(It's very different comparing to AVL Tree, Red-Black Tree, Spaly Tree and so on)
    // Split_child function help B-Tree grows deep when root's number of keys is full.
    int i = x->keysNum;
    if(x->leaf)
    {
        // When x is leaf, put key k into the node.
        while(i >=1 && k < x->keys[i-1])
        {
            x->keys[i] = x->keys[i-1];
            i--;
        }
        x->keys[i] = k;
        (x->keysNum)++;
    }
    else
    {
        // Because x is "not" leaf, recurse til the node is leaf.
        while(i >= 1 && k < x->keys[i-1])
            i--;
        if(x->child[i]->keysNum == 2*t-1)
        {
            Split_child(x, i);
            if(k > x->keys[i])
                i++;
        }
        Insert_nonfull(x->child[i], k);
    }
}

void BTree::Insert(int k)
{
    // At beginning, create a new node as root.
    if(!root)
    {
        root = new Node(t);
        root->keys[0] = k;
        root->keysNum = 1;
        return;
    }
    
    Node* r = root;
    if(r->keysNum == 2*t-1)
    {
        // root's keys if full, and thus create a new key as a new root and the new root's child is old root node.
        Node* s = new Node(t);
        root = s;
        s->leaf = false;
        s->keysNum = 0;
        s->child[0] = r;
        
        // Split old root node into new root node's two children, and the middle key becomes to the root's key
        Split_child(s, 0);
        Insert_nonfull(s, k);
    }
    else
        Insert_nonfull(r, k);
}

// The Search function can be customized.
// In our case, we focus on implement Delete function.
BTree::Address BTree::Search(Node* x, int k)
{
    Address X;
    // Check if root has any key or not.
    // If there is no key, root point to its only child node
    if(root->keysNum == 0)
    {
        root = root->child[0];
        x = root;
    }
    
    // Find index
    int i = 0;
    while(i < x->keysNum && k > x->keys[i])
        i++;
    X.i = i;
    X.node = x;
    
    // If it doesn't exit, node pointer points to NULL and then return it.
    if(x->leaf && x->keys[i] != k)
    {
        X.node = NULL;  // Not finding the key k
        return X;
    }
    
    vect.push_back(X);  // Store the address which have been passed.
    
    // Check whether key k is in the node.
    // If yes, return its location.
    // If no, keep searching.
    if(i < x->keysNum && k == x->keys[i])
        return X;
    else
        return Search(x->child[i], k);
}

void BTree::Merge(Node* x, int i)
{
    // If Left Merge, i--
    // Else, i keeps the same.
    if(i-1 >= 0 && x->child[i-1]->keysNum == t-1)
        i--;
    
    // In the nodes being changed, the private members- keysNum, keys[], and child[]- have to change.
    // Move the key from x to x->child[i], and then merge x->child[i] and x->child[i+1].
    Node* y = x->child[i];
    Node* z = x->child[i+1];
    
    // Node y
    y->keysNum = 2*t-1;
    
    y->keys[t-1] = x->keys[i];
    
    for(int j=0; j<t-1; j++)
        y->keys[j+t] = z->keys[j];
    
    if(!y->leaf)
        for(int j=0; j<t; j++)
            y->child[j+t] = z->child[j];
    
    // Node z
    delete z;
    
    // Ndoe x
    (x->keysNum)--;
    
    for(int j=i; j<x->keysNum; j++)
        x->keys[j] = x->keys[j+1];
    
    for(int j=i + 1; j<x->keysNum + 1; j++)
        x->child[j] = x->child[j+1];
}

void BTree::Move_Down(Node* x, int i)
{
    Node* y;
    Node* z;
    
    // Clockwise Moving
    if(i-1 >= 0 && x->child[i-1]->keysNum > t-1)
    {
        y = x->child[i-1];
        z = x->child[i];
        
        // Node z
        (z->keysNum)++;
        for(int j=z->keysNum-1; j>=0; j--)
            z->keys[j+1] = z->keys[j];
        if(!z->leaf)
            for(int j=z->keysNum; j>=0; j--)
                z->child[j+1] = z->child[j];
        
        z->keys[0] = x->keys[i-1];
        z->child[0] = y->child[y->keysNum];  // Only one step! So even node z is leaf, let the line run.
        
        // Node x
        x->keys[i-1] = y->keys[y->keysNum-1];
        
        // Node y
        (y->keysNum)--;
    }
    else  // Counterclockwise Moving
    {
        y = x->child[i];
        z = x->child[i+1];
        
        // Node y
        (y->keysNum)++;
        y->keys[y->keysNum-1] = x->keys[i];
        y->child[y->keysNum] = z->child[0];  // Only one step! So even node y is leaf, let the line run.
        
        // Node x
        x->keys[i] = z->keys[0];
        
        // Node z
        (z->keysNum)--;
        for(int j=0; j<z->keysNum; j++)
            z->keys[j] = z->keys[j+1];
        if(!z->leaf)
            for(int j=0; j<z->keysNum + 1; j++)
                z->child[j] = z->child[j+1];
    }
}

void BTree::Add_Key(Node* x, int i)
{
    if(vect.size() == 0)
        return;
    
    x = vect.back().node;
    i = vect.back().i;
    vect.pop_back();
    
    // Recursion makes the nodes that have passed through contain at least t keys
    if(x->keysNum == t-1)
        Add_Key(x, i);
    
    if((i-1 >= 0 && x->child[i-1]->keysNum > t-1) || (i+1 <= x->keysNum-1 && x->child[i+1]->keysNum > t-1))
        Move_Down(x, i);
    else
        Merge(x, i);
}

void BTree::Merge_Delete(Node* x, int i)
{
    // In the nodes being changed, the private members- keysNum, keys[], and child[]- have to change.
    // Remove the key k from x and Delete it.
    // Then merge x->child[i] and x->child[i+1].
    Node* y = x->child[i];
    Node* z = x->child[i+1];
    
    // Node y
    for(int j=0; j<t-1; j++)
    {
        y->keys[j+t-1] = z->keys[j];
        
        if(y->leaf)
            y->child[j+t] = z->child[j];
    }
    y->keysNum = 2*t-2;
    
    // Node z
    delete z;
    
    // Node x
    (x->keysNum)--;
    for(int j=i; j<x->keysNum; j++)
    {
        x->keys[j] = x->keys[j+1];
        x->child[j+1] = x->child[j+2];
    }
}

BTree::Address BTree::Nonleaf_Move_Down(Node* x, int i)
{
    Address X;
    
    Node* y = x->child[i];
    Node* z = x->child[i+1];
    
    // Clockwise Moving
    if(y->keysNum > t-1)
    {
        // Node z
        (z->keysNum)++;
        for(int j=z->keysNum-1; j>=0; j--)
            z->keys[j+1] = z->keys[j];
        
        if(!z->leaf)
            for(int j=z->keysNum; j>=0; j--)
                z->child[j+1] = z->child[j];
        
        z->keys[0] = x->keys[i];
        z->child[0] = y->child[y->keysNum];  // Only one step! So even node z is leaf, let the line run.
        
        // Node x
        x->keys[i] = y->keys[y->keysNum-1];
        
        // Node y
        (y->keysNum)--;
        
        X.node = z;
        X.i = 0;
        return X;
    }
    else  // Counterclockwise Moving
    {
        // Node y
        (y->keysNum)++;
        y->keys[y->keysNum-1] = x->keys[i];
        y->child[y->keysNum] = z->child[0];  // Only one step! So even node y is leaf, let the line run.
        
        // Node x
        x->keys[i] = z->keys[0];
        
        // Node z
        (z->keysNum)--;
        for(int j=0; j<z->keysNum; j++)
            z->keys[j] = z->keys[j+1];
        if(!z->leaf)
            for(int j=0; j<z->keysNum + 1; j++)
                z->child[j] = z->child[j+1];
        
        X.node = y;
        X.i = y->keysNum - 1;
        return X;
    }
}

void BTree::Nonleaf_Remove(Node* x, int i)
{
    Node* y = x->child[i];
    Node* z = x->child[i+1];
    
    if(y->keysNum == t-1 && z->keysNum == t-1)
        Merge_Delete(x, i);
    else
    {
        // Key k was moved, x_new and i_new are the new location of key k.
        Address X = Nonleaf_Move_Down(x, i);
        
        if(y->leaf)
            Leaf_Remove(X.node, X.i);
        else
            Nonleaf_Remove(X.node, X.i);
    }
}

//If the key k is in node x and x is a leaf, delete the key k from x.
void BTree::Leaf_Remove(Node* x, int i)
{
    (x->keysNum)--;
    for(int j=i; j<x->keysNum; j++)
        x->keys[j] = x->keys[j+1];
}

void BTree::Delete(int k)
{
    // First, find the node x containing key k.
    Address X = Search(root, k);
    
    Node* x = vect.back().node;
    int i = vect.back().i;
    vect.pop_back();
    
    if(X.node->keysNum == t-1)
        Add_Key(x, i);
    
    X = Search(root, k);
    vect.clear();
    
    if(X.node->leaf)
        Leaf_Remove(X.node, X.i);
    else
        Nonleaf_Remove(X.node, X.i);
}


int main()
{
    BTree b(2);
    
    b.Insert(12);
    b.Insert(8);
    b.Insert(4);
    b.Insert(9);
    b.Insert(3);
    b.Insert(24);
    b.Insert(40);
    b.Insert(7);
    b.Insert(17);
    b.Insert(33);
    b.Insert(84);
    b.Insert(2);
    b.Insert(55);
    
    b.Delete(8);
    b.Delete(40);
    b.Delete(55);
    // b.Delete(12);  // problem
    
    b.Traverse(b.Root());
    std::cout << std::endl;
    
    return 0;
}