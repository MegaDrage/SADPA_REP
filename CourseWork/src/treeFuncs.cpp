#include "treeFuncs.h"

void AVLtreeTraversal(AVLtree* root) {
    if (root) {
        AVLtreeTraversal(root->left);
        printf("%d\n", root->key);
        AVLtreeTraversal(root->right);
    }
}

int maxNum(int a, int b) { return (a > b) ? a : b; }

int sizeOfAVLtree(AVLtree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + sizeOfAVLtree(root->left) + sizeOfAVLtree(root->right);
    }
}

int heightOfAVLtree(AVLtree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + maxNum(heightOfAVLtree(root->left), heightOfAVLtree(root->right));
    }
}

int sumOfLenghtPaths(AVLtree* root, int L) {
    if (!root) {
        return 0;
    } else {
        return L + sumOfLenghtPaths(root->left, L + 1) + sumOfLenghtPaths(root->right, L + 1);
    }
}

int checksumAVLtree(AVLtree* root) {
    if (!root) {
        return 0;
    } else {
        return root->key + checksumAVLtree(root->left) + checksumAVLtree(root->right);
    }
}
double averageHeight(AVLtree* root) { return sumOfLenghtPaths(root, 1) / (double)sizeOfAVLtree(root); }

int isSearchAVLtree(AVLtree* root) {
    if (root && ((root->left && (root->key <= root->left->key || !isSearchAVLtree(root->left))) ||
                 (root->right && (root->key >= root->right->key || !isSearchAVLtree(root->right))))) {
        return 0;
    }
    return 1;
}

void freeAVLtree(AVLtree*& root) {
    if (root) {
        freeAVLtree(root->left);
        delete root;
        freeAVLtree(root->right);
    }
}

int findNode(AVLtree* root, int x) {
    AVLtree* p = root;
    while (p) {
        if (p->key < x) {
            p = p->right;
        } else if (p->key > x) {
            p = p->left;
        } else if (p->key == x) {
            break;
        }
    }
    if (p) {
        return p->key;
    }
    return 0;
}