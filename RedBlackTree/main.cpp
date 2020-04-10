// C++
// Red-Black Tree
// Author: Lee, Shuai-Hsun
#include <iostream>
#include "RB_Tree.h"

int main()
{
    using namespace std;
    
    RBTree rbtree;
    Data a("14", 1);
    Data b("11", 2);
    Data c("17", 3);
    Data d("7", 4);
    Data e("53", 5);
    Data f("4", 6);
    Data g("13", 7);
    Data h("12", 8);
    Data i("8", 9);
    
    rbtree.RBTree_insert(a, 14);
    rbtree.RBTree_insert(b, 11);
    rbtree.RBTree_insert(c, 17);
    rbtree.RBTree_insert(d, 7);
    rbtree.RBTree_insert(e, 53);
    rbtree.RBTree_insert(f, 4);
    rbtree.RBTree_insert(g, 13);
    rbtree.RBTree_insert(h, 12);
    rbtree.RBTree_insert(i, 8);
    
    rbtree.RBTree_delete(53);
    rbtree.RBTree_delete(11);
    rbtree.RBTree_delete(8);
    rbtree.RBTree_delete(12);
    rbtree.RBTree_delete(7);
    rbtree.RBTree_delete(13);
    rbtree.RBTree_delete(4);
    rbtree.RBTree_delete(17);
    rbtree.RBTree_delete(14);
    
    cout << endl;
    rbtree.print(14);
    
    return 0;
}