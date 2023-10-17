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
void RRTurn(AVLtree*& root) {
    AVLtree* q = root->right;
    root->balance = 0;
    q->balance = 0;
    root->right = q->left;
    q->left = root;
    root = q;
}
void LLTurn(AVLtree*& root) {
    AVLtree* q = root->left;
    root->balance = 0;
    q->balance = 0;
    root->left = q->right;
    q->right = root;
    root = q;
}
void RLTurn(AVLtree*& root) {
    AVLtree* q = root->right;
    AVLtree* r = q->left;
    if (r->balance > 0) {
        root->balance = -1;
    } else {
        root->balance = 0;
    }
    if (r->balance < 0) {
        q->balance = 1;
    } else {
        q->balance = 0;
    }
    r->balance = 0;
    q->left = r->right;
    root->right = r->left;
    r->left = root;
    r->right = q;
    root = r;
}

void LRTurn(AVLtree*& root) {
    AVLtree* q = root->left;
    AVLtree* r = q->right;
    if (r->balance < 0) {
        root->balance = 1;
    } else {
        root->balance = 0;
    }
    if (r->balance > 0) {
        q->balance = -1;
    } else {
        q->balance = 0;
    }
    r->balance = 0;
    q->right = r->left;
    root->left = r->right;
    r->left = q;
    r->right = root;
    root = r;
}

void addAVLNode(AVLtree*& root, int data, bool& grows) {
    if (root == nullptr) {
        root = new AVLtree;
        root->key = data;
        root->left = nullptr;
        root->right = nullptr;
        root->balance = 0;
        grows = true;
    } else if (root->key > data) {
        addAVLNode(root->left, data, grows);
        if (grows) {
            if (root->balance > 0) {
                root->balance = 0;
                grows = false;
            } else if (root->balance == 0) {
                root->balance = -1;
                grows = true;
            } else {
                if (root->left->balance < 0) {
                    LLTurn(root);
                    grows = false;
                } else {
                    LRTurn(root);
                    grows = false;
                }
            }
        }
    } else if (root->key < data) {
        addAVLNode(root->right, data, grows);
        if (grows) {
            if (root->balance < 0) {
                root->balance = 0;
                grows = false;
            } else if (root->balance == 0) {
                root->balance = 1;
                grows = true;
            } else {
                if (root->right->balance > 0) {
                    RRTurn(root);
                    grows = false;
                } else {
                    RLTurn(root);
                    grows = false;
                }
            }
        }
    } else {
        // Nothing to do
    }
}

void addNode(AVLtree*& root, int data) {
    bool add = false;
    addAVLNode(root, data, add);
}

bool findNode(AVLtree* root, int x) {
    AVLtree* p = root;
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
        if (root->right->balance >= 0) {
            RR1Turn(root, decreasing);
        } else {
            RLTurn(root);
        }
    }
}
void del(AVLtree*& root, bool& decreasing, AVLtree*& q) {
    if (root->right) {
        del(root->right, decreasing, q);
        if (decreasing) {
            BRTurn(root, decreasing);
        }
    } else {
        q->key = root->key;
        q = root;
        root = root->left;
        decreasing = true;
    }
}
//
void DeleteAVLNode(AVLtree*& root, int x, bool& decreasing) {
    if (!root) {
        return;
    }
    if (root->key > x) {
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
            del(q->left, decreasing, q);
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
#endif