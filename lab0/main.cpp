#include <stdio.h>

#include "libs.h"
int isSearchTree(tree* root);
int main() {
    tree* root = new tree;
    root->key = 19;
    root->left = new tree;
    root->right = NULL;
    root->left->key = 12;
    root->left->left = NULL;
    root->left->right = new tree;
    root->left->right->key = 13;
    root->left->right->left = new tree;
    root->left->right->left->right = NULL;
    root->left->right->left->left = NULL;
    root->left->right->left->key = 10;
    root->left->right->right = new tree;
    root->left->right->right->key = 14;
    root->left->right->right->left = new tree;
    root->left->right->right->right = NULL;
    root->left->right->right->left->key = 8;
    root->left->right->right->left->left = NULL;
    root->left->right->right->left->right = NULL;
    printf("left->root->right\n");
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
