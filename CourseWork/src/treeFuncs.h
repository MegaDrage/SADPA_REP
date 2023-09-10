#ifndef TREEFUNCS_H
#define TREEFUNCS_H
#include <stdio.h>

#include "tree.h"
void AVLtreeTraversal(AVLtree* root);
int maxNum(int a, int b);
int sizeOfAVLtree(AVLtree* root);
int heightOfAVLtree(AVLtree* root);
int sumOfLenghtPaths(AVLtree* root, int L);
int checksumAVLtree(AVLtree* root);
double averageHeight(AVLtree* root);
int isSearchAVLtree(AVLtree* root);
void freeAVLtree(AVLtree*& root);
int findNode(AVLtree* root, int x);
#endif