#ifndef LIBS_H
#define LIBS_H
typedef struct tree {
    int key;
    tree* left;
    tree* right;
} tree;

int sizeOfTree(tree* root);
void freeTree(tree*& root);
int maxNum(int a, int b);
int heightOfTree(tree* root);
int checkSumTree(tree* root);
int sumOfLenPaths(tree* root, int L);
double averageHeight(tree* root);
void treeTraversalInOrder(tree* root);
void treeTraversalPreOrder(tree* root);
void treeTraversalPostOrder(tree* root);
#endif