#ifndef LIBS_HPP
#define LIBS_HPP
#include <stdio.h>
#include <stdlib.h>
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
    tree* p = (tree*)malloc(sizeof(tree));
    p->key = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void insertNodeRec(tree*& root, int data) {
    if (!root) {
        root = createNode(data);
    }
    if (root->key > data) {
        insertNodeRec(root->left, data);
    } else if (root->key < data) {
        insertNodeRec(root->right, data);
    }
}
bool findNode(tree* root, int x) {
    tree* p = root;
    bool isFound = false;
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
        isFound = true;
    }
    return isFound;
}

tree* minNode(tree* root) {
    tree* p = root;
    while (p->right) {
        p = p->right;
    }
    return p;
}

tree* deleteNode(tree* root, int x) {
    if (!root) return root;
    if (root->key > x) {
        root->left = deleteNode(root->left, x);
        return root;
    } else if (root->key < x) {
        root->right = deleteNode(root->right, x);
        return root;
    }

    if (root->left == NULL) {
        tree* temp = root->right;
        free(root);
        return temp;
    } else if (root->right == NULL) {
        tree* temp = root->left;
        free(root);
        return temp;
    } else {
        tree* temp = minNode(root->left);
        root->key = temp->key;
        root->left = deleteNode(root->left, temp->key);
        return root;
    }
}

void deleteNodePointer(tree*& root, int x) {
    tree** p = &root;
    while (*p) {
        if (x < (*p)->key) {
            p = &((*p)->left);
        } else if (x > (*p)->key) {
            p = &((*p)->right);
        } else {
            break;
        }
    }
    if (*p) {
        tree* q = *p;
        if (q->left == NULL) {
            *p = q->right;

        } else if (q->right == NULL) {
            *p = q->left;
        } else {
            tree* r = q->left;
            tree* s = q;
            if (r->right == NULL) {
                r->right = q->right;
                *p = r;
            } else {
                while (r->right != NULL) {
                    s = r;
                    r = r->right;
                }
                s->right = r->left;
                r->left = q->left;
                r->right = q->right;
                *p = r;
            }
        }
        free(q);
    }
}
#endif