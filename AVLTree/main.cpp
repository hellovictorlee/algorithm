// C++
// AVL Tree
// Author: Lee, Shuai-Hsun
#include <iostream>
#include "AVL_Tree.h"

int main()
{
    using namespace std;
    
    AVLTree avltree;
    Data a("14", 1);
    Data b("11", 2);
    Data c("17", 3);
    Data d("7", 4);
    Data e("53", 5);
    Data f("4", 6);
    Data g("13", 7);
    Data h("12", 8);
    Data i("8", 9);
    
    avltree.AVLTree_insert(a, 14);
    avltree.AVLTree_insert(b, 11);
    avltree.AVLTree_insert(c, 17);
    avltree.AVLTree_insert(d, 7);
    avltree.AVLTree_insert(e, 53);
    avltree.AVLTree_insert(f, 4);
    avltree.AVLTree_insert(g, 13);
    avltree.AVLTree_insert(h, 12);
    avltree.AVLTree_insert(i, 8);
    
    avltree.AVLTree_delete(53);
    avltree.AVLTree_delete(11);
    avltree.AVLTree_delete(8);
    avltree.AVLTree_delete(12);
    avltree.AVLTree_delete(7);
    avltree.AVLTree_delete(13);
    avltree.AVLTree_delete(4);
    avltree.AVLTree_delete(17);
    avltree.AVLTree_delete(14);
    
    cout << endl;
    avltree.print(14);
    
    return 0;
}