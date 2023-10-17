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
#include <cmath>
#include <iostream>
#include <queue>

#include "libs.hpp"
int calculateWidth(tree* node);
void drawTree(SDL_Renderer* renderer, tree* node, int x, int y, int spacing);
int calculateWidth(AVLtree* node);
void drawTree(SDL_Renderer* renderer, AVLtree* node, int x, int y, int spacing);
int main() {
    srand(time(NULL));
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL Binary Tree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    int n = 100;
    int a[n] = {0};
    fillInc(a, n);
    tree* IBT = NULL;
    IBT = idealBalancedTree(a, 0, n - 1);
    AVLtree* AVLTree = NULL;
    tree* RBT = NULL;
    bool trc = false;
    bool exist = false;
    for (int j = 0; j < 100;) {
        int randValue = rand() % 200;
        exist = findNode(RBT, randValue);
        if (!exist) {
            insertNodeRec(RBT, randValue);
            j++;
        }
    }
    exist = false;
    for (int i = 0; i < 100;) {
        int randValue = rand() % 200;
        exist = findNode(AVLTree, randValue);
        if (!exist) {
            addAVLNode(AVLTree, randValue, trc);
            i++;
        }
    }
    printf("|---------|------|----------|--------|------------|\n");
    printf("| n = 100 | SIZE | CHECKSUM | HEIGHT | AVG-HEIGHT |\n");
    printf("|---------|------|----------|--------|------------|\n");
    printf("|   IBT   | %3d  |  %6d  |   %2d   |  %lf  |\n", sizeOfTree(IBT), checkSumTree(IBT),
           heightOfTree(IBT), averageHeight(IBT));
    printf("|---------|------|----------|--------|------------|\n");
    printf("|   RBT   | %3d  |  %6d  |    %2d  |  %.5lf   |\n", sizeOfTree(RBT), checkSumTree(RBT),
           heightOfTree(RBT), averageHeight(RBT));
    printf("|---------|------|----------|--------|------------|\n");
    printf("|   AVL   | %3d  |  %6d  |   %2d   |  %lf  |\n", sizeOfAVLtree(AVLTree), checksumAVLtree(AVLTree),
           heightOfAVLtree(AVLTree), averageHeight(AVLTree));
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
        int treeWidth = calculateWidth(AVLTree);
        drawTree(renderer, AVLTree, SCREEN_WIDTH / 2, NODE_RADIUS + 10, treeWidth * (NODE_RADIUS - 8));

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    freeTree(IBT);
    freeTree(RBT);
    freeAVLtree(AVLTree);
    return 0;
}

int calculateWidth(tree* node) {
    if (!node) return 0;
    int leftWidth = calculateWidth(node->left);
    int rightWidth = calculateWidth(node->right);
    return std::max(1, leftWidth + rightWidth);
}

void drawTree(SDL_Renderer* renderer, tree* node, int x, int y, int spacing) {
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
}

int calculateWidth(AVLtree* node) {
    if (!node) return 0;
    int leftWidth = calculateWidth(node->left);
    int rightWidth = calculateWidth(node->right);
    return std::max(1, leftWidth + rightWidth);
}

void drawTree(SDL_Renderer* renderer, AVLtree* node, int x, int y, int spacing) {
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
    snprintf(keyStr, sizeof(keyStr), "%d", node->balance);
    stringRGBA(renderer, x + 10, y - 25, keyStr, 0, 0, 0, 255);
}