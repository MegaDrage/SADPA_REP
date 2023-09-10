#ifndef TREE_H
#define TREE_H
typedef struct AVLtree {
    int key;
    int balance;
    /*
    if b =-1 -- right - left = -1
    if b = 0 --  right - left = 0
    if b = 1 -- right - left = 1
    */
    AVLtree* left;
    AVLtree* right;
} AVLtree;

#endif