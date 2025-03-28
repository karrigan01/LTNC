#define SDL_MAIN_HANDLED
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "grid.h"       // Grid
#include "background.h" // Background
#include "music_background.h" // Music

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 700;

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    initSDL(window, renderer);
    SDL_Texture* bgTexture = loadBackground(renderer, "background.jpg");
    playBackgroundMusic("background.mp3");
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        renderBackground(renderer, bgTexture);
        drawGrid(renderer, 250, 50);
        SDL_RenderPresent(renderer);
    }
    stopMusic();
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
