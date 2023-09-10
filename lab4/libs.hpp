#ifndef LIBS_HPP
#define LIBS_HPP
#include <stdio.h>
#include <stdlib.h>
typedef struct AVLtree {
    int key;
    int balance;
    /*
    if b =-1 -- right - left = -1
    if b = 0 --  right - left = 0
    if b = 1 -- right - left = 1
    */
    AVLtree* left;
    AVLtree* right;
} AVLtree;
typedef struct tree {
    int key;
    int balance;
    /*
    if b =-1 -- right - left = -1
    if b = 0 --  right - left = 0
    if b = 1 -- right - left = 1
    */
    tree* left;
    tree* right;
} tree;
void RRTurn(AVLtree*& root);
void LRTurn(AVLtree*& root);
void LLTurn(AVLtree*& root);
void RLTurn(AVLtree*& root);
int sizeOfAVLtree(AVLtree* root);
int sizeOfTree(tree* root);
int maxNum(int a, int b);
AVLtree* createAVLNode(int data) {
    AVLtree* p = new (AVLtree);
    p->key = data;
    p->left = NULL;
    p->right = NULL;
    p->balance = 0;
    return p;
}
void insertAVLTree(AVLtree*& root, int data, bool& growth) {
    if (!root) {
        root = createAVLNode(data);
        growth = true;
    } else {
        if (root->key > data) {
            insertAVLTree(root->left, data, growth);
            if (growth) {
                if (root->balance > 0) {
                    root->balance = 0;
                    growth = false;
                } else if (root->balance == 0) {
                    root->balance = -1;
                } else {
                    if (root->left->balance < 0) {
                        LLTurn(root);
                    } else {
                        LRTurn(root);
                        growth = false;
                    }
                }
            }
        } else if (root->key < data) {
            insertAVLTree(root->right, data, growth);
            if (growth) {
                if (root->balance < 0) {
                    root->balance = 0;
                    growth = false;
                } else if (root->balance == 0) {
                    root->balance = 1;
                } else {
                    if (root->right->balance > 0) {
                        RRTurn(root);
                    } else {
                        RLTurn(root);
                        growth = false;
                    }
                }
            }
        } else {
            root->key = data;
        }
    }
}
void addAVLNode(AVLtree*& root, int data) {
    bool growth = false;
    insertAVLTree(root, data, growth);
}
/*INSERTING*/
void LLTurn(AVLtree*& root) {
    AVLtree* p = root->left;
    root->balance = 0;
    p->balance = 0;
    root->left = p->right;
    p->right = root;
    root = p;
}
void RRTurn(AVLtree*& root) {
    AVLtree* p = root->right;
    root->balance = 0;
    p->balance = 0;
    root->right = p->left;
    p->left = root;
    root = p;
}

void LRTurn(AVLtree*& root) {
    AVLtree *q = root->left, *r = q->right;
    if (r->balance < 0)
        root->balance = 1;
    else
        root->balance = 0;
    if (r->balance > 0)
        q->balance = -1;
    else
        q->balance = 0;
    r->balance = 0;
    root->left = r->right;
    q->right = r->left;
    r->left = q;
    r->right = root;
    root = r;
}

void RLTurn(AVLtree*& root) {
    AVLtree *q = root->right, *r = q->left;
    if (r->balance > 0)
        root->balance = -1;
    else
        root->balance = 0;
    if (r->balance < 0)
        q->balance = 1;
    else
        q->balance = 0;
    r->balance = 0;
    root->right = r->left;
    q->left = r->right;
    r->left = root;
    r->right = q;
    root = r;
}

/* DELETING TURNS */
void LL1Turn(AVLtree*& root, bool& decreasing) {
    AVLtree* q = root->left;
    if (q->balance == 0) {
        root->balance = -1;
        q->balance = 1;
        decreasing = false;
    } else {
        root->balance = 0;
        q->balance = 0;
    }
    root->left = q->right;
    q->right = root;
    root = q;
}
void BRTurn(AVLtree*& root, bool& decreasing) {
    if (root->balance == 1) {
        root->balance = 0;
    } else if (root->balance == 0) {
        root->balance = -1;
        decreasing = false;
    } else if (root->balance == -1) {
        if (root->left->balance <= 0) {
            LL1Turn(root, decreasing);
        } else {
            LRTurn(root);
        }
    }
}

void RR1Turn(AVLtree*& root, bool& decreasing) {
    AVLtree* q = root->right;
    if (q->balance == 0) {
        root->balance = 1;
        q->balance = -1;
        decreasing = false;
    } else {
        root->balance = 0;
        q->balance = 0;
    }
    root->right = q->left;
    q->left = root;
    root = q;
}
void BLTurn(AVLtree*& root, bool& decreasing) {
    if (root->balance == -1) {
        root->balance = 0;
    } else if (root->balance == 0) {
        root->balance = 1;
        decreasing = false;
    } else if (root->balance == 1) {
        if (root->left->balance >= 0) {
            RR1Turn(root, decreasing);
        } else {
            RLTurn(root);
        }
    }
}
void del(AVLtree*& root, bool& decreasing) {
    if (root->right) {
        del(root->right, decreasing);
        if (decreasing) {
            BRTurn(root, decreasing);
        }
    } else {
        AVLtree* q = root;
        root = q;
        decreasing = true;
    }
}
//
void DeleteAVLNode(AVLtree*& root, int x, bool& decreasing) {
    if (!root) {
        return;
    } else if (root->key > x) {
        DeleteAVLNode(root->left, x, decreasing);
        if (decreasing) {
            BLTurn(root, decreasing);
        }
    } else if (root->key < x) {
        DeleteAVLNode(root->right, x, decreasing);
        if (decreasing) {
            BRTurn(root, decreasing);
        }
    } else {
        AVLtree* q = root;
        if (!(q->right)) {
            root = q->left;
            decreasing = true;
        } else if (!(q->left)) {
            root = q->right;
            decreasing = true;
        } else {
            del(root->left, decreasing);
            if (decreasing) {
                BLTurn(root, decreasing);
            }
        }
        delete q;
    }
}

void deleteNode(AVLtree*& root, int data) {
    bool decreasing = false;
    DeleteAVLNode(root, data, decreasing);
}
int isHeightBalanced(AVLtree* root, bool& isBalanced) {
    if (root == nullptr || !isBalanced) {
        return 0;
    }
    int left_height = isHeightBalanced(root->left, isBalanced);
    int right_height = isHeightBalanced(root->right, isBalanced);
    if (abs(left_height - right_height) > 1) {
        isBalanced = false;
    }
    return maxNum(left_height, right_height) + 1;
}
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

int sumOfLenPaths(AVLtree* root, int L) {
    if (!root) {
        return 0;
    } else {
        return L + sumOfLenPaths(root->left, L + 1) + sumOfLenPaths(root->right, L + 1);
    }
}

int checksumAVLtree(AVLtree* root) {
    if (!root) {
        return 0;
    } else {
        return root->key + checksumAVLtree(root->left) + checksumAVLtree(root->right);
    }
}
double averageHeight(AVLtree* root) { return sumOfLenPaths(root, 1) / (double)sizeOfAVLtree(root); }

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

void fillInc(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 100;
    }
}
#endif