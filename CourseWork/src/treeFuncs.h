#ifndef TREE_FUNCS_H
#define TREE_FUNCS_H
#include <stdio.h>

#include "list.h"
#include "tree.h"
void AVLtreeTraversal(AVLtree* root);
void RRTurn(AVLtree*& root);
void LLTurn(AVLtree*& root);
void RLTurn(AVLtree*& root);
void addNode(AVLtree*& root, list* data);
void LRTurn(AVLtree*& root);
void addAVLNode(AVLtree*& root, list* data, bool& grows);
void freeAVLtree(AVLtree*& root);
std::vector<list*> findNode(AVLtree* root, int x);
#endif