#include "libs.hpp"

void printTree(struct tree* root, int level);
int main() {
    int n = 12;
    int a[n] = {0};
    fillInc(a, n);
    tree* root = NULL;
    root = idealBalancedTree(a, 0, n - 1);
    printf("left->root->right\n");
    treeTraversalInOrder(root);
    printf("SIZE OF TREE: %d\n", sizeOfTree(root));
    printf("CHECKSUM OF TREE: %d\n", checkSumTree(root));
    printf("HEIGHT OF TREE: %d\n", heightOfTree(root));
    printf("AVERAGE HEIGHT OF TREE: %lf\n", averageHeight(root));
    printf("SEARCH: %d", isSearchTree(root));
    printTree(root, 0);
    freeTree(root);
    return 0;
}

void printTree(struct tree* root, int space) {
    if (root == NULL) {
        return;
    }
    space += 3;
    printTree(root->right, space);
    printf("\n");
    for (int i = 3; i < space; i++) {
        printf(" ");
    }
    printf("-|%d|-\n", root->key);
    printTree(root->left, space);
}