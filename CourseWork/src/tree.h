#ifndef TREE_H
#define TREE_H
typedef struct tree {
    int key;
    tree* left;
    tree* right;
} tree;

#endif