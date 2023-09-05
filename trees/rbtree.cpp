#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void treeTraversal(tree* root);
int sizeOfTree(tree* root);
int heightOfTree(tree* root);
double averageHeight(tree* root);
int sumOfLenghtPaths(tree* root, int L);
int checksumTree(tree* root);
void freeTree(tree*& root);
int findNode(tree* root, int x);
int isSearchTree(tree* root);
void insertNode(tree*& root, int data);
void deleteNode(tree*& root, int data);
tree* createNode(int data);
int maxNum(int, int);
int main() {
    tree* basic = NULL;
    insertNode(basic, 10);
    insertNode(basic, 5);
    insertNode(basic, 20);
    deleteNode(basic, 10);
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

tree* createNode(int data) {
    tree* p = new (tree);
    p->key = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void deleteNode(tree*& root, int data) {
    tree** p = &root;
    while (*p) {
        if ((*p)->key < data) {
            p = &((*p)->right);
        } else if ((*p)->key > data) {
            p = &((*p)->left);
        } else {
            break;
        }
    }
    if (*p) {
        tree* q = *p;
        if (!(q->left)) {
            *p = q->right;
        } else if (!(q->right)) {
            *p = q->left;
        } else {
            tree* r = q->left;
            tree* s = q;
            while (r->right) {
                s = r;
                r = r->right;
            }
            s->right = r->left;
            r->left = q->right;
            r->right = q->right;
            *p = r;
        }
        delete q;
    }
}
void insertNode(tree*& root, int data) {
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

void freeTree(tree*& root) {
    if (root) {
        freeTree(root->left);
        delete root;
        freeTree(root->right);
    }
}
int isSearchTree(tree* root) {
    if (root && ((root->left && (root->key <= root->left->key || !isSearchTree(root->left))) ||
                 (root->right && (root->key >= root->right->key || !isSearchTree(root->right))))) {
        return 0;
    }
    return 1;
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