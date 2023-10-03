#include <iostream>

struct optTree {
    // bool use = false;
    int w;
    int key;
    optTree* left;
    optTree* right;
};

void getAW(int** matrix, int n, optTree** V) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            matrix[i][j] = matrix[i][j - 1] + V[j - 1]->w;
        }
    }
}

void getAPnAR(int**& AW, int n, int**& AP, int**& AR) {
    for (int i = 0; i < n - 1; i++) {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }
    for (int h = 2; h < n; h++) {
        for (int i = 0; i < n - h; i++) {
            int j = i + h;
            int m = AR[i][j - 1];
            int min = AP[i][m - 1] + AP[m][j];
            for (int k = m + 1; k < AR[i + 1][j]; k++) {
                int x = AP[i][k - 1] + AP[k][j];
                if (x < min) {
                    m = k, min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}

void addNode(optTree*& root, optTree**& V, int k) {
    if (root == nullptr) {
        root = new optTree;
        root->key = V[k]->key;
        root->w = V[k]->w;
        root->left = nullptr;
        root->right = nullptr;
    } else {
        if (root->key > V[k]->key) {
            addNode(root->left, V, k);
        } else if (root->key < V[k]->key) {
            addNode(root->right, V, k);
        }
    }
}

void createTree(optTree*& root, int L, int R, int**& AR, optTree**& V) {
    if (L < R) {
        int k = AR[L][R];
        addNode(root, V, k - 1);
        createTree(root, L, k - 1, AR, V);
        createTree(root, k, R, AR, V);
    }
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void freeTree(optTree*& root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

void treeTraverse(optTree* root) {
    if (root) {
        treeTraverse(root->left);
        std::cout << root->key << "\t " << root->w << std::endl;
        treeTraverse(root->right);
    }
}

void treeRootTraverse(optTree* root) {
    if (root) {
        std::cout << root->key << "\t " << root->w << std::endl;
        treeTraverse(root->left);
        treeTraverse(root->right);
    }
}