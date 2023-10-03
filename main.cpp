#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cmath>
#include <cstdlib>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1024;
const int NODE_RADIUS = 20;
const int VERTICAL_SPACING = 70;
const int HORIZONTAL_SPACING = 40;

struct Tree {
    int key;
    Tree* left;
    Tree* right;
    Tree(int k) : key(k), left(nullptr), right(nullptr) {}
};

void drawTree(SDL_Renderer* renderer, Tree* node, int x, int y) {
    if (!node) return;

    // Draw left child
    if (node->left) {
        int xLeft = x - (HORIZONTAL_SPACING + NODE_RADIUS);
        int yLeft = y + VERTICAL_SPACING;
        lineRGBA(renderer, x, y, xLeft, yLeft, 0, 0, 0, 255); // Black line to left child
        drawTree(renderer, node->left, xLeft, yLeft);
    }

    // Draw right child
    if (node->right) {
        int xRight = x + (HORIZONTAL_SPACING + NODE_RADIUS);
        int yRight = y + VERTICAL_SPACING;
        lineRGBA(renderer, x, y, xRight, yRight, 0, 0, 0, 255); // Black line to right child
        drawTree(renderer, node->right, xRight, yRight);
    }

    // Draw node
    filledCircleRGBA(renderer, x, y, NODE_RADIUS, 255, 255, 255, 255); // White fill
    circleRGBA(renderer, x, y, NODE_RADIUS, 0, 0, 0, 255); // Black border

    // Draw key
    char keyStr[10];
    snprintf(keyStr, sizeof(keyStr), "%d", node->key);
    stringRGBA(renderer, x - 5, y - 5, keyStr, 0, 0, 0, 255); // Black key text
}

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL Binary Tree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Example binary tree
    Tree* root = new Tree(5);
    root->left = new Tree(3);
    root->right = new Tree(7);
    root->left->left = new Tree(1);
    root->left->right = new Tree(4);

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255); // Light gray background
        SDL_RenderClear(renderer);

        drawTree(renderer, root, SCREEN_WIDTH / 2, NODE_RADIUS + 10);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Clean up the tree
    // ... (remember to recursively delete all nodes)
    delete root; // This only deletes the root, you will need to delete all nodes properly

    return 0;
}
