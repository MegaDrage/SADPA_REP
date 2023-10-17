#include <iostream>

struct optTree {
    int w;
    int key;
    optTree *left = nullptr, *right = nullptr;
};

void getAW(long** matrix, int n, optTree** V) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            matrix[i][j] = matrix[i][j - 1] + V[j - 1]->w;
        }
    }
}

void getAPnAR(long**& AW, int n, long**& AP, long**& AR) {
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
            for (int k = m + 1; k <= AR[i + 1][j]; k++) {
                int x = AP[i][k - 1] + AP[k][j];
                if (x < min) {
                    m = k;
                    min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}

// void calculateAwApAR(int n, int**& Aw, int**& Ap, int**& AR, optTree**& weights) {
//     for (int i = 0; i < n; i++) {
//         Aw[i][i] = 0;
//         Ap[i][i] = 0;
//         AR[i][i] = 0;
//     }
//     int minK = 0;
//     for (int len = 2; len < n; len++) {
//         for (int i = 0; i < n - len + 1; i++) {
//             int j = i + len - 1;
//             Aw[i][j] = Aw[i][j - 1] + weights[j - 1]->w;
//             Ap[i][j] = Aw[i][j] + Ap[i][i] + Ap[i + 1][j];

//             minK = i;
//             int minCost = Ap[i][i] + Ap[i + 1][j];

//             for (int k = i + 1; k <= j; k++) {
//                 int temp = Ap[i][k - 1] + Ap[k][j];
//                 if (temp < minCost) {
//                     minCost = temp;
//                     minK = k;
//                 }
//             }

//             AR[i][j] = minK;
//         }
//     }
//     AR[0][n] = minK;
// }

optTree* addNode(optTree**& V, int k) {
    optTree* p = new optTree;
    p->key = V[k]->key;
    p->w = V[k]->w;
    return p;
}

void createTree(optTree*& root, int L, int R, long**& AR, optTree**& V) {
    if (L < R) {
        int k = AR[L][R];
        root = addNode(V, k - 1);
        createTree(root->left, L, k - 1, AR, V);
        createTree(root->right, k, R, AR, V);
    }
}

void printMatrix(long** matrix, int n) {
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

int maxNum(int a, int b) { return (a > b) ? a : b; }

int sizeOfOptTree(optTree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + sizeOfOptTree(root->left) + sizeOfOptTree(root->right);
    }
}

int heightOfOptTree(optTree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + maxNum(heightOfOptTree(root->left), heightOfOptTree(root->right));
    }
}

int sumOfLenPaths(optTree* root, int L) {
    if (!root) {
        return 0;
    } else {
        return L * root->w + sumOfLenPaths(root->left, L + 1) + sumOfLenPaths(root->right, L + 1);
    }
}

int checksumOptTree(optTree* root) {
    if (!root) {
        return 0;
    } else {
        return root->key + checksumOptTree(root->left) + checksumOptTree(root->right);
    }
}

int fullWeight(optTree** V, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += V[i]->w;
    }
    return sum;
}

double averageHeight(optTree* root, optTree** V, int n) {
    return sumOfLenPaths(root, 1) / (double)fullWeight(V, n);
}
