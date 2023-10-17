#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <time.h>

#include <cmath>
#include <cstdlib>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int NODE_RADIUS = 20;
const int VERTICAL_SPACING = 70;

#include "libs.hpp"
int calculateWidth(optTree* node);
void drawTree(SDL_Renderer* renderer, optTree* node, int x, int y, int spacing);
int main() {
    srand(time(NULL));
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL Binary Tree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    int n = 101;
    long** AR = new long*[n];
    long** AW = new long*[n];
    long** AP = new long*[n];
    for (int i = 0; i < n; i++) {
        AR[i] = new long[n];
        AW[i] = new long[n];
        AP[i] = new long[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AR[i][j] = 0;
            AW[i][j] = 0;
            AP[i][j] = 0;
        }
    }
    optTree** V = new optTree*[n - 1];

    for (int i = 0; i < n - 1; i++) {
        V[i] = new optTree;
        V[i]->key = i;
        V[i]->w = i + 1 + rand() % 20;
    }
    for (int i = 0; i < n - 1; i++) {
        std::cout << "---" << V[i]->w << " ---" << std::endl;
    }
    // calculateAwApAR(n, AW, AP, AR, V);
    getAW(AW, n, V);
    printMatrix(AW, n);
    getAPnAR(AW, n, AP, AR);
    // AR[0][1] = 1;
    // AR[0][2] = 2;
    // AR[0][3] = 3;
    // AR[1][2] = 2;
    // AR[1][3] = 3;
    // AR[2][3] = 3;
    printMatrix(AP, n);
    printMatrix(AR, n);
    optTree* OptTree = nullptr;
    createTree(OptTree, 0, n - 1, AR, V);
    // treeRootTraverse(OptTree);
    printf("|---------|------|----------|--------|------------|\n");
    printf("| n = 100 | SIZE | CHECKSUM | HEIGHT | AVG-HEIGHT |\n");
    printf("|---------|------|----------|--------|------------|\n");
    printf("|   OPT   | %3d  |  %6d  |   %3d  |  %.5lf  |\n", sizeOfOptTree(OptTree),
           checksumOptTree(OptTree), heightOfOptTree(OptTree), averageHeight(OptTree, V, n - 1));
    printf("|---------|------|----------|--------|------------|\n");
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
    SDL_RenderClear(renderer);
    int treeWidth = calculateWidth(OptTree);
    drawTree(renderer, OptTree, SCREEN_WIDTH / 2, NODE_RADIUS + 10, (treeWidth - 18) * (NODE_RADIUS -
    5));

    SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    /*Remove memory*/
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
    freeTree(OptTree);
    return 0;
}

int calculateWidth(optTree* node) {
    if (!node) return 0;
    int leftWidth = calculateWidth(node->left);
    int rightWidth = calculateWidth(node->right);
    return std::max(1, leftWidth + rightWidth);
}

void drawTree(SDL_Renderer* renderer, optTree* node, int x, int y, int spacing) {
    if (!node) return;

    // Draw left child
    if (node->left) {
        int xLeft = x - spacing;
        int yLeft = y + VERTICAL_SPACING;
        lineRGBA(renderer, x, y, xLeft, yLeft, 0, 0, 0, 255);
        drawTree(renderer, node->left, xLeft, yLeft, spacing / 2);
    }

    // Draw right child
    if (node->right) {
        int xRight = x + spacing;
        int yRight = y + VERTICAL_SPACING;
        lineRGBA(renderer, x, y, xRight, yRight, 0, 0, 0, 255);
        drawTree(renderer, node->right, xRight, yRight, spacing / 2);
    }

    // Draw node
    filledCircleRGBA(renderer, x, y, NODE_RADIUS, 255, 255, 255, 255);
    circleRGBA(renderer, x, y, NODE_RADIUS, 0, 0, 0, 255);

    // Draw key
    char keyStr[10];
    snprintf(keyStr, sizeof(keyStr), "%d", node->key);
    stringRGBA(renderer, x - 5, y - 5, keyStr, 0, 0, 0, 255);
    snprintf(keyStr, sizeof(keyStr), "%d", node->w);
    stringRGBA(renderer, x + 25, y - 10, keyStr, 0, 0, 0, 255);
}