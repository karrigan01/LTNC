#define SDL_MAIN_HANDLED
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "grid.h"
#include "background.h"
#include "music_background.h"
#include "tetromino.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 700;
int DROP_SPEED = 500; // Tetromino drop delay in milliseconds

// Game grid (false = empty, true = occupied)
bool grid[GRID_HEIGHT][GRID_WIDTH] = {false};

// Store colors of placed blocks
SDL_Color gridColors[GRID_HEIGHT][GRID_WIDTH] = {};

// Draw placed blocks with stored colors
void drawPlacedBlocks(SDL_Renderer* renderer) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (grid[i][j]) {
                SDL_SetRenderDrawColor(renderer, gridColors[i][j].r, gridColors[i][j].g, gridColors[i][j].b, 255);
                SDL_Rect block = { j * BLOCK_SIZE + 250, i * BLOCK_SIZE + 50, BLOCK_SIZE, BLOCK_SIZE };
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
}

// Store Tetromino in grid when it lands
bool running = true;
void placeTetromino(Tetromino& tetromino) {
    SDL_Color color = tetromino.color;

    for (int i = 0; i < tetromino.shape.size(); i++) {
        for (int j = 0; j < tetromino.shape[i].size(); j++) {
            if (tetromino.shape[i][j]) {
                if (tetromino.y + i>=GRID_HEIGHT||tetromino.x + j>=GRID_WIDTH||grid[tetromino.y + i][tetromino.x + j]){
                    running=false;
                    return;
                }
                grid[tetromino.y + i][tetromino.x + j] = true;
                gridColors[tetromino.y + i][tetromino.x + j] = color;
            }
        }
    }
}

// Remove full lines and shift down
long long scorre=0;
void clearFullLines() {
    for (int i = GRID_HEIGHT - 1; i >= 0; i--) {
        bool full = true;
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (!grid[i][j]) {
                full = false;
                break;
            }
        }

        if (full) {
            scorre+=100;
            // Move all rows above down
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < GRID_WIDTH; j++) {
                    grid[k][j] = grid[k - 1][j];
                    gridColors[k][j] = gridColors[k - 1][j];
                }
            }

            // Clear the top row
            for (int j = 0; j < GRID_WIDTH; j++) {
                grid[0][j] = false;
                gridColors[0][j] = {255,255,255, 255}; // Default white
            }

            // Recheck this row
            i++;
        }
    }
}

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer,TTF_Font* &font) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    font = TTF_OpenFont("arial.ttf", 24); // Ensure the file exists
    SDL_Color white = {255, 255, 255};
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
void renderScore(SDL_Renderer* renderer, TTF_Font* font, long long score) {
    SDL_Color white = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, ("Score: " + to_string(score)).c_str(), white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {20, 20, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
void renderGameover(SDL_Renderer* renderer, TTF_Font* font){
    SDL_Color red = {255, 0, 0, 255}; // Red color
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over!", red);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {SCREEN_WIDTH / 2 - surface->w / 2, SCREEN_HEIGHT / 2 - surface->h / 2, surface->w, surface->h};

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
void renderWin(SDL_Renderer* renderer, TTF_Font* font){
    SDL_Color red = {255, 255, 0, 255}; // Yellow color
    SDL_Surface* surface = TTF_RenderText_Solid(font, "You Win!", red);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {SCREEN_WIDTH / 2 - surface->w / 2, SCREEN_HEIGHT / 2 - surface->h / 2, surface->w, surface->h};

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font= nullptr;
    initSDL(window, renderer,font);
    SDL_Texture* bgTexture = loadBackground(renderer, "background.jpg");
    playBackgroundMusic("background.mp3");

    Tetromino currentTetromino(rand() % 8);
    SDL_Event event;
    Uint32 lastDropTime = SDL_GetTicks();

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        currentTetromino.moveLeft(grid);
                        break;
                    case SDLK_RIGHT:
                        currentTetromino.moveRight(grid);
                        break;
                    case SDLK_DOWN:
                        currentTetromino.moveDown(grid);
                        break;
                    case SDLK_UP:
                        currentTetromino.rotate(grid);
                        break;
                }
            }
        }

        // Move Tetromino down automatically
        if (SDL_GetTicks() - lastDropTime > DROP_SPEED) {
            if (currentTetromino.moveDown(grid)) {
                lastDropTime = SDL_GetTicks();
            } else {
                placeTetromino(currentTetromino);
                if (!running){
                renderGameover(renderer,font);
                SDL_RenderPresent(renderer);
                SDL_Delay(3000);
                break;
                }
                clearFullLines();
                currentTetromino = Tetromino(rand() % 8);
            }
        }
        if (scorre==1000){
        renderWin(renderer,font);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
        break;
        }
        // Render everything
        SDL_RenderClear(renderer);
        renderBackground(renderer, bgTexture);
        drawGrid(renderer, 250, 50);
        drawPlacedBlocks(renderer);
        drawTetromino(renderer, currentTetromino);
        renderScore(renderer, font, scorre);
        SDL_RenderPresent(renderer);
    }

    stopMusic();
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    //cout<<score<<'\n';
    return 0;
}
