#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <vector>
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int NODE_RADIUS = 20;
const int VERTICAL_SPACING = 70;
#include "libs.hpp"
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
    stringRGBA(renderer, x + 15, y - 25, keyStr, 0, 0, 0, 255);
}
int main() {
    srand(time(NULL));
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL Binary Tree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    AVLtree* AVLTree = NULL;

    bool exist = false;
    // for (int i = 0; i < 10; i++) {
    //     addNode(AVLTree, i);
    // }
    std::vector<int> values;
    for (int i = 0; i < 100;) {
        int randValue = rand() % 200;
        exist = findNode(AVLTree, randValue);
        if (exist == 0) {
            values.push_back(randValue);
            addNode(AVLTree, randValue);
            i++;
        }
    }
    AVLtreeTraversal(AVLTree);
    int i = 0;
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
    SDL_RenderClear(renderer);
    SDL_Delay(100);
    // int key;
    while (i < 100) {
        // scanf("%d", &key);
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderClear(renderer);
        int treeWidth = calculateWidth(AVLTree);
        drawTree(renderer, AVLTree, SCREEN_WIDTH / 2, NODE_RADIUS + 10, treeWidth * (NODE_RADIUS - 8));
        char keyStr[10];
        char del[16] = "Deleting node: ";
        snprintf(keyStr, 16, "%s", del);
        stringRGBA(renderer, 0, 1, keyStr, 0, 0, 0, 255);
        snprintf(keyStr, sizeof(keyStr), "%d", values[i]);
        stringRGBA(renderer, 120, 1, keyStr, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        printf("Deleting node: %d\n", values[i]);
        deleteNode(AVLTree, values[i]);
        printf("\nAfter removing: \n\n");
        AVLtreeTraversal(AVLTree);
        i++;
    }
    freeAVLtree(AVLTree);
    return 0;
}
