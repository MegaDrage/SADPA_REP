#ifndef TREE_H
#define TREE_H
#include "list.h"
#include <vector>
typedef struct AVLtree {
    std::vector <list*> key;
    int balance;
    /*
    if b =-1 -- right - left = -1
    if b = 0 --  right - left = 0
    if b = 1 -- right - left = 1
    */
    AVLtree* left = nullptr;
    AVLtree* right = nullptr;
} AVLtree;
#endif