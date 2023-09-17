#include "libs.h"

#include <stdio.h>
int sizeOfTree(tree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + sizeOfTree(root->left) + sizeOfTree(root->right);
    }
}

void freeTree(tree*& root) {
    if (root) {
        freeTree(root->left);
        delete root;
        freeTree(root->right);
    }
}
int maxNum(int a, int b) { return (a > b) ? a : b; }
int heightOfTree(tree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + maxNum(heightOfTree(root->left), heightOfTree(root->right));
    }
}

int checkSumTree(tree* root) {
    if (!root) {
        return 0;
    } else {
        return root->key + checkSumTree(root->left) + checkSumTree(root->right);
    }
}

int sumOfLenPaths(tree* root, int L) {
    if (!root) {
        return 0;
    } else {
        return L + sumOfLenPaths(root->left, L + 1) + sumOfLenPaths(root->right, L + 1);
    }
}
double averageHeight(tree* root) { return sumOfLenPaths(root, 1) / (double)sizeOfTree(root); }
void treeTraversalInOrder(tree* root) {
    if (root) {
        treeTraversalInOrder(root->left);
        printf("%d\n", root->key);
        treeTraversalInOrder(root->right);
    }
}

void treeTraversalPreOrder(tree* root) {
    if (root) {
        printf("%d\n", root->key);
        treeTraversalPreOrder(root->left);
        treeTraversalPreOrder(root->right);
    }
}

void treeTraversalPostOrder(tree* root) {
    if (root) {
        treeTraversalPostOrder(root->right);
        printf("%d\n", root->key);
        treeTraversalPostOrder(root->left);
    }
}
