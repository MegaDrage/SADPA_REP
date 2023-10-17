#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int NODE_RADIUS = 20;
const int VERTICAL_SPACING = 70;
#include "libs.hpp"
int calculateWidth(B_tree* node);
void drawTree(SDL_Renderer* renderer, B_tree* node, int x, int y, int spacing);
int main() {
    srand(time(NULL));
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL Binary Tree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    B_tree* tree = nullptr;
    AVLtree* AVLTree = nullptr;
    bool exist = false;
    for (int i = 0; i < 100;) {
        int randValue = rand() % 200;
        exist = findNode(AVLTree, randValue);
        if (!exist) {
            addAVL(AVLTree, randValue);
            i++;
        }
    }

    for (int i = 0; i < 20;) {
        int randValue = rand() % 200;
        exist = findNode(tree, randValue);
        if (!exist) {
            addBTreeNode(tree, randValue);
            i++;
        }
    }
    printf("|---------|------|----------|--------|------------|\n");
    printf("| n = 100 | SIZE | CHECKSUM | HEIGHT | AVG-HEIGHT |\n");
    printf("|---------|------|----------|--------|------------|\n");
    printf("|   BTR   | %3d  |  %6d  |   %2d   |  %lf  |\n", sizeOfTree(tree), checkSumTree(tree),
           heightOfTree(tree), averageHeight(tree));
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
        int treeWidth = calculateWidth(tree);
        drawTree(renderer, tree, SCREEN_WIDTH / 2, NODE_RADIUS + 10, treeWidth * (NODE_RADIUS - 10));

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    freeTree(tree);
    freeAVLtree(AVLTree);
    return 0;
}

int calculateWidth(B_tree* node) {
    if (!node) return 0;
    int leftWidth = calculateWidth(node->left);
    int rightWidth = calculateWidth(node->right);
    return std::max(1, leftWidth + rightWidth);
}

void drawTree(SDL_Renderer* renderer, B_tree* node, int x, int y, int spacing) {
    if (!node) return;
    int xLeft = x - spacing;
    int xRight = x + spacing;
    int yLevel = y;
    if (node->balance == 0) {
        yLevel = y + VERTICAL_SPACING;
    }
    if (node->left) {
        lineRGBA(renderer, x, y, xLeft, yLevel, 0, 0, 0, 255);
        drawTree(renderer, node->left, xLeft, yLevel, spacing / 2);
    }

    if (node->right) {
        lineRGBA(renderer, x, y, xRight, yLevel, 0, 0, 0, 255);
        drawTree(renderer, node->right, xRight, yLevel, spacing / 2);
    }

    filledCircleRGBA(renderer, x, y, NODE_RADIUS, 255, 255, 255, 255);
    circleRGBA(renderer, x, y, NODE_RADIUS, 0, 0, 0, 255);

    char keyStr[10];
    snprintf(keyStr, sizeof(keyStr), "%d", node->key);
    stringRGBA(renderer, x - 5, y - 5, keyStr, 0, 0, 0, 255);
    snprintf(keyStr, sizeof(keyStr), "%d", node->balance);
    stringRGBA(renderer, x + 15, y - 25, keyStr, 0, 0, 0, 255);
}

// void drawTree(SDL_Renderer* renderer, B_tree* node, int x, int y, int spacing) {
//     if (!node) return;
//     int xLeft = x - spacing;
//     int xRight = x + spacing;
//     int yLevel = y;
//     if (node->balance == 0) {
//         yLevel = y + VERTICAL_SPACING;
//     }

//     filledCircleRGBA(renderer, x, y, NODE_RADIUS, 255, 255, 255, 255);
//     circleRGBA(renderer, x, y, NODE_RADIUS, 0, 0, 0, 255);

//     char keyStr[10];
//     snprintf(keyStr, sizeof(keyStr), "%d", node->key);
//     stringRGBA(renderer, x - 5, y - 5, keyStr, 0, 0, 0, 255);
//     drawTree(renderer, node->right, xRight, yLevel, spacing / 2);
//     drawTree(renderer, node->left, xLeft, yLevel, spacing / 2);
// }