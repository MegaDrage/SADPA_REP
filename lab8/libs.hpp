#ifndef __LIBS_HPP
#define __LIBS_HPP
#include <iostream>
struct tree {
    int key;
    tree* left = nullptr;
    tree* right = nullptr;
    bool use;
    int w;
};
void insertNodeRec(tree*& root, tree* child);
void A1Alg(tree*& root, int n, tree**& V) {
    for (int i = 0; i < n; i++) {
        V[i]->use = false;
    }
    for (int i = 0; i < n; i++) {
        int max = 0;
        int index = 0;
        for (int j = 0; j < n; j++) {
            if (!(V[j]->use) && V[j]->w > max) {
                max = V[j]->w;
                index = j;
            }
        }
        V[index]->use = true;
        insertNodeRec(root, V[index]);
    }
}

tree* addNode(tree**& V, int k) {
    tree* p = new tree;
    p->key = V[k]->key;
    p->w = V[k]->w;
    return p;
}

void getAW(long** matrix, int n, tree** V) {
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            matrix[i][j] = matrix[i][j - 1] + V[j - 1]->w;
        }
    }
}

void getAPnAR(long**& AW, int n, long**& AP, long**& AR) {
    for (int i = 0; i <= n - 1; i++) {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }
    for (int h = 2; h <= n; h++) {
        for (int i = 0; i <= n - h; i++) {
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

void createTree(tree*& root, int L, int R, long**& AR, tree**& V) {
    if (L < R) {
        int k = AR[L][R];
        root = addNode(V, k - 1);
        createTree(root->left, L, k - 1, AR, V);
        createTree(root->right, k, R, AR, V);
    }
}

void A2Alg(tree*& root, int n, tree**& V, int L, int R) {
    if (L <= R) {
        int weight = 0;
        int minWeightDiff = 1000000;
        int bestRoot = -1;

        for (int i = L; i <= R; i++) {
            weight += V[i]->w;
        }

        for (int i = L; i <= R; i++) {
            int leftWeight = 0;
            int rightWeight = 0;

            for (int j = L; j < i; j++) {
                leftWeight += V[j]->w;
            }

            for (int j = i + 1; j <= R; j++) {
                rightWeight += V[j]->w;
            }

            int weightDiff = abs(leftWeight - rightWeight);

            if (weightDiff < minWeightDiff) {
                minWeightDiff = weightDiff;
                bestRoot = i;
            }
        }

        root = new tree;
        root->key = V[bestRoot]->key;
        root->w = V[bestRoot]->w;
        root->left = nullptr;
        root->right = nullptr;

        A2Alg(root->left, n, V, L, bestRoot - 1);
        A2Alg(root->right, n, V, bestRoot + 1, R);
    }
}

int sizeOfTree(tree* root) {
    if (!root) {
        return 0;
    } else {
        return 1 + sizeOfTree(root->left) + sizeOfTree(root->right);
    }
}

// int fullWeight(tree* root) {
//     if (!root) {
//         return 0;
//     } else {
//         return root->w + fullWeight(root->left) + sizeOfTree(root->right);
//     }
// }

void freeTree(tree*& root) {
    if (root) {
        freeTree(root->left);
        delete root;
        freeTree(root->right);
    }
}

int fullWeight(tree** V, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += V[i]->w;
    }
    return sum;
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
        return L * root->w + sumOfLenPaths(root->left, L + 1) + sumOfLenPaths(root->right, L + 1);
    }
}
double averageHeight(tree* root, tree** V, int n) {
    return sumOfLenPaths(root, 1) / (double)fullWeight(V, n);
}

void treeTraversalInOrder(tree* root) {
    if (root) {
        treeTraversalInOrder(root->left);
        printf("%d\n", root->key);
        treeTraversalInOrder(root->right);
    }
}

void insertNodeRec(tree*& root, tree* child) {
    if (!root) {
        root = new tree;
        root->key = child->key;
        root->w = child->w;
        root->left = nullptr;
        root->right = nullptr;
        return;
    }
    if (root->key > child->key) {
        insertNodeRec(root->left, child);
    } else if (root->key < child->key) {
        insertNodeRec(root->right, child);
    }
    else {
        
    }
}
#endif  // __LIBS_HPP