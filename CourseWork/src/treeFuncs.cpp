#include "treeFuncs.h"

#include "list.h"
#include "record.h"
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

void addNode(AVLtree*& root, list* data) {
    bool basic = false;
    addAVLNode(root, data, basic);
}

void addAVLNode(AVLtree*& root, list* data, bool& grows) {
    if (root == nullptr) {
        root = new AVLtree;
        root->key.push_back(data);
        root->left = nullptr;
        root->right = nullptr;
        root->balance = 0;
        grows = true;
    } else if (root->key.front()->data.appNumber > data->data.appNumber) {
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
    } else if (root->key.front()->data.appNumber < data->data.appNumber) {
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
        root->key.push_back(data);
    }
}



void AVLtreeTraversal(AVLtree* root) {
    if (root) {
        AVLtreeTraversal(root->left);
        showRecord(root->key.front()->data);
        AVLtreeTraversal(root->right);
    }
}


void freeAVLtree(AVLtree*& root) {
    if (root != nullptr) {
        freeAVLtree(root->left);
        freeAVLtree(root->right);
        delete root;
    }
}

std::vector<list*> findNode(AVLtree* root, int x) {
    AVLtree* p = root;
    while (p) {
        if (p->key.front()->data.appNumber < x) {
            p = p->right;
        } else if (p->key.front()->data.appNumber > x) {
            p = p->left;
        } else if (p->key.front()->data.appNumber == x) {
            break;
        }
    }
    if (p) {
        return p->key;
    }
    return std::vector<list*>(0);
}