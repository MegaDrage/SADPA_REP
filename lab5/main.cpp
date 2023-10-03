#include <stdlib.h>
#include <time.h>

#include "libs.hpp"
void printTree(struct AVLtree* root, int level);
void printTree(struct tree* root, int level);
int main() {
    srand(time(NULL));
    AVLtree* AVLTree = NULL;

    // bool exist = false;
    bool add = false;
    for (int i = 0; i < 10; i++) {
        addAVLNode(AVLTree, i, add);
    }
    // for (int i = 0; i < 10;) {
    //     int randValue = rand() % 200;
    //     exist = findNode(AVLTree, randValue);
    //     if (exist == 0) {
    //         addAVLNode(AVLTree, randValue, add);
    //         i++;
    //     }
    // }
    deleteNode(AVLTree, 5);
    AVLtreeTraversal(AVLTree);
    // int i = 0;
    // int key;
    // while (i < 10) {
    //     scanf("%d", &key);
    //     deleteNode(AVLTree, key);
    //     i++;
    // }

    freeAVLtree(AVLTree);
    return 0;
}