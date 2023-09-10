#ifndef LIBS_HPP
#define LIBS_HPP

#include <stdio.h>
typedef struct tree {
    int key;
    struct tree* left;
    struct tree* right;
} tree;
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
        treeTraversalPostOrder(root->left);
        treeTraversalPostOrder(root->right);
        printf("%d\n", root->key);
    }
}

int isSearchTree(tree* root) {
    if (root && ((root->left && (root->key <= root->left->key || !isSearchTree(root->left))) ||
                 (root->right && (root->key >= root->right->key || !isSearchTree(root->right))))) {
        return 0;
    }
    return 1;
}
tree* createNode(int data) {
    tree* p = new (tree);
    p->key = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void insertNodeRec(tree*& root, int data) {
    if (!root) {
        root = createNode(data);
        return;
    }
    if (root->key > data) {
        insertNodeRec(root->left, data);
    } else if (root->key < data) {
        insertNodeRec(root->right, data);
    }
}

void insertNodePP(tree*& root, int data) {
    tree** p = &root;
    while (*p) {
        if (data < (*p)->key) {
            p = &((*p)->left);
        } else if (data > (*p)->key) {
            p = &((*p)->right);
        } else {
            break;
        }
    }
    if (!(*p)) {
        *p = createNode(data);
    }
}

int findNode(tree* root, int x) {
    tree* p = root;
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
tree* idealBalancedTree(int* arr, int L, int R) {
    tree* p = new tree;
    if (L > R) {
        p = NULL;
    } else {
        int mid = (L + R) / 2;
        p->key = arr[mid];
        p->left = idealBalancedTree(arr, L, mid - 1);
        p->right = idealBalancedTree(arr, mid + 1, R);
    }
    return p;
}

void fillInc(int* A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}
void swapArrElem(int* A, int* B) {
    int temp = *A;
    *A = *B;
    *B = temp;
}

void QuickSort(int* A, int L, int R) {
    while (L < R) {
        int x = A[(L + R) / 2];
        int i = L;
        int j = R;
        while (i <= j) {
            while (A[i] < x) {
                i++;
            }
            while (A[j] > x) {
                j--;
            }
            if (i <= j) {
                swapArrElem(&A[i], &A[j]);
                i++;
                j--;
            }
        }
        if (j - L > R - i) {
            QuickSort(A, L, j);
            L = i;
        } else {
            QuickSort(A, i, R);
            R = j;
        }
    }
}
#endif