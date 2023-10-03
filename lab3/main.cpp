#include <stdlib.h>
#include <time.h>

#include "libs.hpp"
void printTree(struct tree* root, int level);
int main() {
    srand(time(NULL));
    tree* RBT = NULL;
    bool exist = false;
    for (int i = 0; i < 10;) {
        int randValue = rand() % 300;
        exist = findNode(RBT, randValue);
        if (!exist) {
            insertNodeRec(RBT, randValue);
            i++;
        }
    }
    printf("Before: \n");
    treeTraversalInOrder(RBT);
    int i = 0;
    while (i < 10) {
        int key = 0;
        scanf("%d", &key);
        deleteNodePointer(RBT, key);
        printf("After deletion: \n");
        treeTraversalInOrder(RBT);
        i++;
    }
    // NEXT WORK
    treeTraversalInOrder(RBT);
    // printTree(RBT, 0);
    freeTree(RBT);
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