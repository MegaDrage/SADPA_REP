#include <stdlib.h>
#include <time.h>

#include "libs.hpp"
void printTree(struct tree* root, int level);
int main() {
    srand(time(NULL));
    int n = 100;
    int a[n] = {0};
    fillInc(a, n);
    tree* IBT = NULL;
    IBT = idealBalancedTree(a, 0, n - 1);
    tree* RBT = NULL;
    int exist = 0;
    for (int i = 0; i < 100;) {
        int randValue = rand() % 300;
        exist = findNode(RBT, randValue);
        if (!exist) {
            insertNodeRec(RBT, randValue);
            i++;
        }
    }
    printf("|---------|------|----------|--------|------------|\n");
    printf("| n = 100 | SIZE | CHECKSUM | HEIGHT | AVG-HEIGHT |\n");
    printf("|---------|------|----------|--------|------------|\n");
    printf("|   IBT   | %3d  |  %6d  |   %2d   |  %lf  |\n", sizeOfTree(IBT), checkSumTree(IBT),
           heightOfTree(IBT), averageHeight(IBT));
    printf("|---------|------|----------|--------|------------|\n");
    printf("|   RBT   | %3d  |  %6d  |   %2d   |  %lf  |\n", sizeOfTree(RBT), checkSumTree(RBT),
           heightOfTree(RBT), averageHeight(RBT));
    printf("|---------|------|----------|--------|------------|\n");
    printf("\n----\t-----RBT-----\t----\n");
    printTree(RBT, 0);
    freeTree(RBT);
    printf("\n----\t-----IBT-----\t----\n");
    printTree(IBT, 0);
    freeTree(IBT);
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