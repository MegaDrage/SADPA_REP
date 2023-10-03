#include <iostream>

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

struct B_tree {
    int key;
    int balance;
    B_tree* left;
    B_tree* right;
};
void RRTurn(AVLtree*& root);
void LRTurn(AVLtree*& root);
void LLTurn(AVLtree*& root);
void RLTurn(AVLtree*& root);
int sizeOfAVLtree(AVLtree* root);
int maxNum(int a, int b);
void addNode(B_tree*& root, int data, bool& VR, bool& HR) {
    if (root == nullptr) {
        root = new B_tree;
        root->key = data;
        root->left = nullptr;
        root->right = nullptr;
        root->balance = 0;
        VR = true;
    } else {
        if (root->key > data) {
            addNode(root->left, data, VR, HR);
            if (VR) {
                if (root->balance == 0) {
                    B_tree* q = root->left;
                    root->left = q->right;
                    q->right = root;
                    root = q;
                    q->balance = 1;
                    VR = false;
                    HR = true;
                } else {
                    root->balance = 0;
                    HR = true;
                }
            } else {
                HR = false;
            }
        } else if (root->key < data) {
            addNode(root->right, data, VR, HR);
            if (VR) {
                root->balance = 1;
                VR = false;
                HR = true;
            } else if (HR) {
                if (root->balance > 0) {
                    B_tree* q = root->right;
                    root->right = q->left;
                    root->balance = 0;
                    q->balance = 0;
                    q->left = root;
                    root = q;
                    VR = true;
                    HR = false;
                } else {
                    HR = false;
                }
            }
        }
    }
}

void traversal(B_tree* root) {
    if (root) {
        traversal(root->left);
        std::cout << root->key << std::endl;
        traversal(root->right);
    }
}

int sizeOfTree(B_tree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + sizeOfTree(root->left) + sizeOfTree(root->right);
    }
}
int maxNum(int a, int b) { return (a > b) ? a : b; }
int heightOfTree(B_tree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + maxNum(heightOfTree(root->left), heightOfTree(root->right));
    }
}

int checkSumTree(B_tree* root) {
    if (!root) {
        return 0;
    } else {
        return root->key + checkSumTree(root->left) + checkSumTree(root->right);
    }
}

int sumOfLenPaths(B_tree* root, int L) {
    if (!root) {
        return 0;
    } else {
        return L + sumOfLenPaths(root->left, L + 1) + sumOfLenPaths(root->right, L + 1);
    }
}
double averageHeight(B_tree* root) { return sumOfLenPaths(root, 1) / (double)sizeOfTree(root); }

void freeTree(B_tree*& root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

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

bool findNode(B_tree* root, int x) {
    B_tree* p = root;
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