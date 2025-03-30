#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "tetromino.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 700;
long long scorre=0,maxscore=0;
bool running = true;//keep playing or not
bool grid[GRID_HEIGHT][GRID_WIDTH] = {false};
SDL_Color gridColors[GRID_HEIGHT][GRID_WIDTH] = {};
mt19937_64 rng(10101994);
void renderScore(SDL_Renderer* renderer, TTF_Font* font, long long score) {
    SDL_Color white = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, ("Score: " + to_string(score)).c_str(), white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {20, 20, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
void renderMaxScore(SDL_Renderer* renderer, TTF_Font* font, long long maxscore){
    SDL_Color white = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, ("Max Score: " + to_string(maxscore)).c_str(), white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {20, 40, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
void renderGameover(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color red= {255, 0, 0};

    SDL_Surface* surface1 = TTF_RenderText_Solid(font, "Game Over", red);
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_Rect rect1 = {SCREEN_WIDTH / 2 - surface1->w / 2, SCREEN_HEIGHT / 2 - 50, surface1->w, surface1->h};

    SDL_Surface* surface2 = TTF_RenderText_Solid(font, "Press R to Restart", red);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_Rect rect2 = {SCREEN_WIDTH / 2 - surface2->w / 2, SCREEN_HEIGHT / 2, surface2->w, surface2->h};

    SDL_RenderCopy(renderer, texture1, NULL, &rect1);
    SDL_RenderCopy(renderer, texture2, NULL, &rect2);

    SDL_FreeSurface(surface1);
    SDL_DestroyTexture(texture1);
    SDL_FreeSurface(surface2);
    SDL_DestroyTexture(texture2);
}

void renderWin(SDL_Renderer* renderer, TTF_Font* font){
    SDL_Color red = {255, 255, 0, 255}; // Yellow color
    SDL_Surface* surface = TTF_RenderText_Solid(font, "You Win! \nPress R", red);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {SCREEN_WIDTH / 2 - surface->w / 2, SCREEN_HEIGHT / 2 - surface->h / 2, surface->w, surface->h};

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
void restartGame(Tetromino &currentTetromino, long long &score) {
    running=true;
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = false;
            gridColors[i][j] = {0, 0, 0, 255}; // Reset to black
        }
    }
    currentTetromino = Tetromino(rng() % 7);
    score = 0;
}

#endif // SYSTEM_H_INCLUDED
