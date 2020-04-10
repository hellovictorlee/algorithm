// C++
// Fibonacci Heaps
// Author: Lee, Shuai-Hsun
#include <iostream>
#include <math.h>
#include <vector>

class FiboHeap
{
    // A structure to represent an Fibonacci heaps node
    struct Node { int key; int degree; bool mark; struct Node* parent; struct Node* child; struct Node* left; struct Node* right; };
private:
    Node Min;
    
    // heapMin not only record the information of the minimun key value node address but also the address of root list.
    Node* heapMin;
    
    int nodeNum;
    int listNum;
    
    // It's impossible using DecreaseKey and Delete function directly without knowing node address.
    // Therefore, in my case, create vector storing every node address so that DecreaseKey and Delete function can work.
    // Use to store pointer array pointing every node in Fibonacci heap.
    // For the using of DecreaseKey and Delete
    std::vector<Node*> vect;
    int index;
public:
    FiboHeap(): heapMin(NULL), nodeNum(0), listNum(0), index(-1) { Min.key = 0; Min.degree = -1; Min.mark = false; Min.parent = NULL; Min.child = NULL; Min.left = NULL; Min.right = NULL; }
    ~FiboHeap() {}
    Node* NodeCreate(int k);
    void ListInsert(Node* list, Node* x);
    void Insert(int k);
    void ListRemove(Node* z);
    void Link(Node* x, Node* y);
    void Consolidate();
    Node ExtractMin();
    void CascadingCut(Node* y);
    void Cut(Node* x, Node* y);
    void DecreaseKey(Node* x, int k);
    void Delete(Node* x);
    
    // Get the total exit node number in the Fibonacci Heaps
    int Size();
    
    // Use to store pointer array pointing every node in Fibonacci heap.
    // For the using of DecreaseKey and Delete
    Node* Vector(int i);
};

// Create a new node
FiboHeap::Node* FiboHeap::NodeCreate(int k)
{
    Node* x = new Node;
    x->key = k;
    x->degree = 0;
    x->mark = false;
    x->parent = NULL;
    x->child = NULL;
    x->left = x;
    x->right = x;
    
    // Every time when we create a new node, we store the node address in the vector which can be used in DecreaseKey and Delete fuction.
    vect.push_back(x);
    
    return x;
}

// Make a node(or even a list) insert into another list
void FiboHeap::ListInsert(Node* list, Node* x)
{
    if(x == x->right)
    {
        list->right->left = x;
        x->right = list->right;
    }
    else
    {
        list->right->left = x->left;
        x->left->right = list->right;
    }
    list->right = x;
    x->left = list;
}

// Insert function which is used to insert the new nodes
// After inserting a node, it becomes its own heap tree, and is then added to the root list
void FiboHeap::Insert(int k)
{
    Node* x = NodeCreate(k);
    
    if(heapMin == NULL)
        // create a root list for Fibonacci heaps only containing x
        heapMin = x;
    else
    {
        ListInsert(heapMin, x);
        
        // Checking if the new inserted node(new heap tree) has the minimun key value or not
        if(x->key < heapMin->key)
            heapMin = x;
    }
    nodeNum++;
    listNum++;
}

// In our case, we only use the function to remove a node from a list which has at least 2 nodes
void FiboHeap::ListRemove(Node* z)
{
    if(z != z->right)
    {
        z->right->left = z->left;
        z->left->right = z->right;
    }
}

// The fuction is for the fact that move a tree whose root is y to be as x's one child
void FiboHeap::Link(Node* x, Node* y)
{
    // Remove y from the root list
    // NOTICE: ListRemove only remove the relation between y and its original list
    // Original list is fine, but y itself need to do some work for its independence.
    ListRemove(y);
    // The following two line is the work for y's independance
    y->left = y;
    y->right = y;
    
    // Make y a child of x, and at meanwhile, increment x's degree
    if(x->child == NULL)
        x->child = y;
    else
        ListInsert(x->child, y);
    (x->degree)++;
    y->parent = x;
    
    // mark y node false
    y->mark = false;
}

// In my opinion, Consolidate is the most challenging function here.
// The basic idea is that compare all the heap trees, and then if each two of the same degree heap tree merges together.
// Finally, there are one or more heap trees with all different degrees in Fibonacci heaps.
// Find the smallest key root as heapMin.
void FiboHeap::Consolidate()
{
    // A[D] uses to store root address of different degree heap trees
    int D = log(nodeNum) / log((1+sqrt(5))/2);
    Node* A[D];
    for(int i=0; i<D; ++i)
        A[i] = NULL;
    
    // In our case, we use for loop to go through every root of heap trees in turn.
    // If we find the two same degree heap trees, and then make larger key value one a child of smaller key value one.
    Node* w = heapMin;
    int k = listNum;
    for(int i=0; i<k; i++)
    {
        Node* x = w;
        w = w->right;
        int d = x->degree;
        while(d < D && A[d] != NULL)
        {
            Node* y = A[d];
            if(x->key > y->key)
            {
                // Exchange x with y
                Node* temp;
                temp = x;
                x = y;
                y = temp;
            }
            Link(x, y);
            listNum--;
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }
    
    // All node address storing in A links together as new root list.
    heapMin = NULL;
    for(int i=0; i<D; i++)
    {
        if(A[i] != NULL)
        {
            if(heapMin == NULL)
            {
                // Create a root list containing A[i]
                heapMin = A[i];
            }
            else
            {
                ListInsert(heapMin, A[i]);
                if(A[i]->key < heapMin->key)
                    heapMin = A[i];
            }
        }
    }
}

// There are three main step:
// 1. Remove heapMin node
// 2. All heapMin childs move to root list
// 3. Go Consolidate function
FiboHeap::Node FiboHeap::ExtractMin()
{
    Node* z = heapMin;
    if(z != NULL)
    {
        Node* x = z->child;
        if(x != NULL)
        {
            // Add x to the root list
            Node* temp = x;
            do
            {
                listNum++;
                temp = temp->right;
            }while(temp != x);
            ListInsert(heapMin, x);
            x->parent = NULL;
        }
        
        // Remove z from the root list
        ListRemove(z);
        listNum--;
        if(z == z->right)
            heapMin = NULL;
        else
        {
            heapMin = z->right;
            Consolidate();
        }
        nodeNum--;
    }
    Min = *z;
    delete z;
    return Min;
}

// The mark attributes help obtain the desired time bounds which records a little piece of the history of each node.
// CascadingCut procedure recurses its way up the tree until it finds either a root or an unmarked node.
void FiboHeap::CascadingCut(Node* y)
{
    Node* z = y->parent;
    if(z != NULL)
    {
        if(y->mark == false)
            y->mark = true;
        else
        {
            Cut(y, z);
            CascadingCut(z);
        }
    }
}

// Cut moves DecreaseKey node to root list.
void FiboHeap::Cut(Node* x, Node* y)
{
    // Remove x from the child list of y, and decrement y's degree
    if(x == x->right)
        y->child = NULL;
    else
    {
        if(y->child == x)
            y->child = x->right;
        ListRemove(x);
        x->right = x;
        x->left = x;
    }
    y->degree--;
    
    // Add x to the root list
    ListInsert(heapMin, x);
    listNum++;
    
    x->parent = NULL;
    x->mark = false;
}

// DecreaseKey consists of Cut and CascadingCut.
// Cut moves DecreaseKey node to root list.
// CascadingCut procedure use to obtains the desired time bounds
void FiboHeap::DecreaseKey(Node* x, int k)
{
    if(k > x->key)
        std::cout << "error! new key is greater than current key" << std::endl;
    x->key = k;
    Node* y = x->parent;
    if(y != NULL && x->key < y->key)
    {
        Cut(x, y);
        CascadingCut(y);
    }
    
    if(x->key < heapMin->key)
        heapMin = x;
}

// Delete consists of DecreaseKey and ExtractMin
void FiboHeap::Delete(Node* x)
{
    // Update Vector which records the exist node address
    std::vector<Node*>::iterator iter = vect.begin() + index;
    vect.erase(iter);
    
    DecreaseKey(x, -2147483648);
    ExtractMin();
}

int FiboHeap::Size()
{
    return nodeNum;
}

FiboHeap::Node* FiboHeap::Vector(int i)
{
    index = i;
    return vect[index];
}


int main()
{
    FiboHeap heap;
    heap.Insert(7);
    heap.Insert(3);
    heap.Insert(9);
    heap.Insert(1);
    heap.Insert(4);
    
    // Vector[0] = 7
    heap.Delete(heap.Vector(0));
    
    // Vector[0] = 3
    heap.DecreaseKey(heap.Vector(0), 0);
    
    // Vector[1] = 9
    heap.Delete(heap.Vector(1));
    
    int times = heap.Size();
    for(int i=0; i<times-1; i++)
        std::cout << heap.ExtractMin().key << " -> ";
    std::cout << heap.ExtractMin().key << std::endl;
    
    return 0;
}