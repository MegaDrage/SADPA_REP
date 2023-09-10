#include <stdlib.h>
#include <time.h>

#include "libs.hpp"
void printTree(struct tree* root, int level);
int main() {
    srand(time(NULL));
    tree* RBT = NULL;
    int exist = 0;
    for (int i = 0; i < 100;) {
        int randValue = rand() % 20;
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
        RBT = deleteNode(RBT, key);
        printf("After deletion: \n");
        treeTraversalInOrder(RBT);
        i++;
    }
    //NEXT WORK
    printTree(RBT, 0);
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