#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "libs.hpp"
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int NODE_RADIUS = 20;
const int VERTICAL_SPACING = 70;
void drawTree(SDL_Renderer* renderer, tree* node, int x, int y, int spacing);
int calculateWidth(tree* node);
int main() {
    srand(time(NULL));
    // SDL_Window* window = nullptr;
    // SDL_Renderer* renderer = nullptr;

    // SDL_Init(SDL_INIT_VIDEO);

    // window = SDL_CreateWindow("SDL Binary Tree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    //                           SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    int n = 100;
    tree* OptTree = nullptr;
    tree* root = nullptr;
    tree* Alg2 = nullptr;
    tree** V = new tree*[n];
    long** AR = new long*[n + 1];
    long** AW = new long*[n + 1];
    long** AP = new long*[n + 1];
    for (int i = 0; i <= n; i++) {
        AR[i] = new long[n + 1];
        AW[i] = new long[n + 1];
        AP[i] = new long[n + 1];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            AR[i][j] = 0;
            AW[i][j] = 0;
            AP[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        V[i] = new tree;
        V[i]->key = i + 1;
        V[i]->w = i + 1 + rand() % 500;
    }
    getAW(AW, n, V);
    getAPnAR(AW, n, AP, AR);
    createTree(OptTree, 0, n, AR, V);
    A1Alg(root, n, V);
    A2Alg(Alg2, n, V, 0, n - 1);
    printf("|---------|------|----------|--------|------------|\n");
    printf("| n = 100 | SIZE | CHECKSUM | HEIGHT | AVG-HEIGHT |\n");
    printf("|---------|------|----------|--------|------------|\n");
    printf("|   OPT   | %3d  |  %6d  |   %3d  |  %.6lf  |\n", sizeOfTree(OptTree), checkSumTree(OptTree),
           heightOfTree(OptTree), averageHeight(OptTree, V, n));
    printf("|---------|------|----------|--------|------------|\n");
    printf("|   Al1   | %3d  |  %6d  |   %3d  |  %.6lf  |\n", sizeOfTree(root), checkSumTree(root),
           heightOfTree(root), averageHeight(root, V, n));
    printf("|---------|------|----------|--------|------------|\n");
    printf("|   Al2   | %3d  |  %6d  |   %3d  |  %.6lf  |\n", sizeOfTree(Alg2), checkSumTree(Alg2),
           heightOfTree(Alg2), averageHeight(Alg2, V, n));
    printf("|---------|------|----------|--------|------------|\n");
    // bool quit = false;
    // SDL_Event e;
    // while (!quit) {
    //     while (SDL_PollEvent(&e) != 0) {
    //         if (e.type == SDL_QUIT) {
    //             quit = true;
    //         }
    //     }

    //     SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
    //     SDL_RenderClear(renderer);
    //     int treeWidth = calculateWidth(root);
    //     drawTree(renderer, root, SCREEN_WIDTH / 2, NODE_RADIUS + 10, (treeWidth - 18) * (NODE_RADIUS - 5));

    //     SDL_RenderPresent(renderer);
    // }

    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();
    for (int i = 0; i < n; i++) {
        delete[] V[i];
    }
    delete[] V;
    freeTree(root);
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
    snprintf(keyStr, sizeof(keyStr), "%d", node->w);
    stringRGBA(renderer, x + 25, y - 10, keyStr, 0, 0, 0, 255);
}