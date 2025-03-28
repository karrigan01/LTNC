#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <SDL.h>
const int ROWS = 20;
const int COLS = 10;
const int CELL_SIZE = 30;

void drawGrid(SDL_Renderer* renderer, int startX, int startY) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i <= ROWS; i++) {
        SDL_RenderDrawLine(renderer, startX, startY + i * CELL_SIZE, startX + COLS * CELL_SIZE, startY + i * CELL_SIZE);
    }
    for (int j = 0; j <= COLS; j++) {
        SDL_RenderDrawLine(renderer, startX + j * CELL_SIZE, startY, startX + j * CELL_SIZE, startY + ROWS * CELL_SIZE);
    }
}


#endif // GRID_H_INCLUDED
