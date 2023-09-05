#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void treeTraversal(tree* root);
int sizeOfTree(tree* root);
void fillrandint(int* A, int n);
tree* idealBalancedTree(int* arr, int L, int R);
void QuickSort(int* A, int L, int R);
void swapArrElem(int* A, int* B);
int heightOfTree(tree* root);
double averageHeight(tree* root);
int sumOfLenghtPaths(tree* root, int L);
int checksumTree(tree* root);
void freeTree(tree*& root);
int findNode(tree* root, int x);
int isSearchTree(tree* root);
int maxNum(int, int);
int main() {
    int arr[20];
    fillrandint(arr, 20);
    QuickSort(arr, 0, 19);
    tree* basic = idealBalancedTree(arr, 0, 19);
    printf("SIZE OF TREE: %d\n", sizeOfTree(basic));
    printf("HEIGHT OF TREE: %d\n", heightOfTree(basic));
    printf("AVERAGE HEIGHT: %lf\n", averageHeight(basic));
    printf("CHECKSUM: %d\n", checksumTree(basic));
    printf("SEARCH TREE: %d\n", isSearchTree(basic));
    printf("FOUND: %d\n", findNode(basic, 22));
    treeTraversal(basic);
    freeTree(basic);
    return 0;
}

void treeTraversal(tree* root) {
    if (root) {
        treeTraversal(root->left);
        printf("%d\n", root->key);
        treeTraversal(root->right);
    }
}

int maxNum(int a, int b) { return (a > b) ? a : b; }

int sizeOfTree(tree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + sizeOfTree(root->left) + sizeOfTree(root->right);
    }
}

int heightOfTree(tree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + maxNum(heightOfTree(root->left), heightOfTree(root->right));
    }
}

int sumOfLenghtPaths(tree* root, int L) {
    if (!root) {
        return 0;
    } else {
        return L + sumOfLenghtPaths(root->left, L + 1) + sumOfLenghtPaths(root->right, L + 1);
    }
}

int checksumTree(tree* root) {
    if (!root) {
        return 0;
    } else {
        return root->key + checksumTree(root->left) + checksumTree(root->right);
    }
}
double averageHeight(tree* root) { return sumOfLenghtPaths(root, 1) / (double)sizeOfTree(root); }

void freeTree(tree*& root) {
    if (root) {
        freeTree(root->left);
        delete root;
        freeTree(root->right);
    }
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

void fillrandint(int* A, int n) {
    srand(time(NULL));
    for (long long i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
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

void swapArrElem(int* A, int* B) {
    int temp = *A;
    *A = *B;
    *B = temp;
}

int isSearchTree(tree* root) {
    if ((root && (root->left && ((root->key <= root->left->key) || !isSearchTree(root->left)))) ||
        (root->left && (root->key >= root->right->key || !isSearchTree(root->right)))) {
        return 0;
    } else {
        return 1;
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