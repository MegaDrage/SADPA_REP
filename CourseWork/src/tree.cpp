#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void AVLtreeTraversal(AVLtree* root);
int maxNum(int a, int b);
int sizeOfAVLtree(AVLtree* root);
int heightOfAVLtree(AVLtree* root);
int sumOfLenghtPaths(AVLtree* root, int L);
int checksumAVLtree(AVLtree* root);
double averageHeight(AVLtree* root);
int isSearchAVLtree(AVLtree* root);
void freeAVLtree(AVLtree*& root);
int findNode(AVLtree* root, int x);
void insertAVLTree(AVLtree*& root, int data, bool& growth);
AVLtree* createAVLNode(int data);
int isHeightbalanced(AVLtree* root, bool& isbalanced);
void addAVLNode(AVLtree*& root, int data);
void LLTurn(AVLtree*& root);
void RRTurn(AVLtree*& root);
void LRTurn(AVLtree*& root);
void LRTurn(AVLtree*& root);
void BRTurn(AVLtree*& root, bool& decreasing);
void BLTurn(AVLtree*& root, bool& decreasing);
void LL1Turn(AVLtree*& root, bool& decreasing);
void RR1Turn(AVLtree*& root, bool& decreasing);
void del(AVLtree*& root, bool& decreasing);
void DeleteAVLNode(AVLtree*& root, int x, bool& decreasing);
void deleteNode(AVLtree*& root, int data);
int main() {
    AVLtree* basic = NULL;
    addAVLNode(basic, 10);
    addAVLNode(basic, 20);
    addAVLNode(basic, 5);
    addAVLNode(basic, 6);
    addAVLNode(basic, 7);
    addAVLNode(basic, 8);
    addAVLNode(basic, 9);
    deleteNode(basic, 6);
    deleteNode(basic, 7);
    deleteNode(basic, 8);
    deleteNode(basic, 9);
    bool balanced = true;
    printf("SIZE OF AVLtree: %d\n", sizeOfAVLtree(basic));
    printf("HEIGHT OF AVLtree: %d\n", heightOfAVLtree(basic));
    printf("AVERAGE HEIGHT: %lf\n", averageHeight(basic));
    printf("CHECKSUM: %d\n", checksumAVLtree(basic));
    printf("SEARCH AVLtree: %d\n", isSearchAVLtree(basic));
    printf("FOUND: %d\n", findNode(basic, 22));
    isHeightbalanced(basic, balanced);
    printf("IS balanced: %d\n", balanced);
    AVLtreeTraversal(basic);
    freeAVLtree(basic);
    return 0;
}
AVLtree* createAVLNode(int data) {
    AVLtree* p = new (AVLtree);
    p->key = data;
    p->left = NULL;
    p->right = NULL;
    p->balance = 0;
    return p;
}

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

void deleteNode(AVLtree*& root, int data) {
    bool decreasing = false;
    DeleteAVLNode(root, data, decreasing);
}
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

void addAVLNode(AVLtree*& root, int data) {
    bool growth = false;
    insertAVLTree(root, data, growth);
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
int isHeightbalanced(AVLtree* root, bool& isbalanced) {
    if (root == nullptr || !isbalanced) {
        return 0;
    }
    int left_height = isHeightbalanced(root->left, isbalanced);
    int right_height = isHeightbalanced(root->right, isbalanced);
    if (abs(left_height - right_height) > 1) {
        isbalanced = false;
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