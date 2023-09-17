#include <stdio.h>

#include "libs.h"
int isSearchTree(tree* root);
int main() {
    tree* root = new tree;
    root->key = 1;
    root->left = new tree;
    root->left->key = 2;
    root->left->right = new tree;
    root->left->right->key = 3;
    root->left->right->right = new tree;
    root->left->right->right->key = 5;
    root->left->right->left = new tree;
    root->left->right->left->key = 4;
    root->left->right->left->right = new tree;
    root->left->right->left->right->key = 7;
    root->left->right->left->left = new tree;
    root->left->right->left->left->key = 6;
    root->left->right->left->left->left = new tree;
    root->left->right->left->left->left->key = 8;
    treeTraversalInOrder(root);
    printf("right->root->left\n");
    treeTraversalPostOrder(root);
    printf("root->left->right\n");
    treeTraversalPreOrder(root);
    printf("SIZE OF TREE: %d\n", sizeOfTree(root));
    printf("CHECKSUM OF TREE: %d\n", checkSumTree(root));
    printf("HEIGHT OF TREE: %d\n", heightOfTree(root));
    printf("AVERAGE HEIGHT OF TREE: %lf\n", averageHeight(root));
    printf("SEARCH: %d", isSearchTree(root));
    freeTree(root);
    return 0;
}

int isSearchTree(tree* root) {
    if (root && ((root->left && (root->key <= root->left->key || !isSearchTree(root->left))) ||
                 (root->right && (root->key >= root->right->key || !isSearchTree(root->right))))) {
        return 0;
    }
    return 1;
}
