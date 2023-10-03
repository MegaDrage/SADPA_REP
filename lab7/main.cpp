
#include "libs.hpp"
int main() {
    int n = 4;
    int** AR = new int*[n];
    int** AW = new int*[n];
    int** AP = new int*[n];
    for (int i = 0; i < n; i++) {
        AR[i] = new int[n];
        AW[i] = new int[n];
        AP[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AR[i][j] = 0;
            AW[i][j] = 0;
            AP[i][j] = 0;
        }
    }
    optTree** V = new optTree*[n - 1];
    V[0] = new optTree;
    V[0]->key = 1;
    V[0]->w = 60;
    V[1] = new optTree;
    V[1]->key = 2;
    V[1]->w = 30;
    V[2] = new optTree;
    V[2]->key = 3;
    V[2]->w = 10;
    getAW(AW, n, V);
    getAPnAR(AW, n, AP, AR);
    printMatrix(AW, n);
    printMatrix(AR, n);
    optTree* root = nullptr;
    createTree(root, 0, n - 1, AR, V);
    treeRootTraverse(root);
    for (int i = 0; i < n; i++) {
        delete[] AR[i];
        delete[] AW[i];
        delete[] AP[i];
    }
    for (int i = 0; i < n - 1; i++) {
        delete[] V[i];
    }
    delete[] AW;
    delete[] AP;
    delete[] AR;
    delete[] V;
    freeTree(root);
    return 0;
}