#ifndef TETROMINO_H_INCLUDED
#define TETROMINO_H_INCLUDED

#include <SDL.h>
#include <vector>

using namespace std;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;
const int BLOCK_SIZE = 30;  // Size of each block in pixels
SDL_Color colors[] = {
    {255, 0, 0, 255},   // Red for shape 0
    {0, 255, 0, 255},   // Green for shape 1
    {0, 0, 255, 255},   // Blue for shape 2
    {255, 255, 0, 255}, // Yellow for shape 3
    {255, 165, 0, 255}, // Orange for shape 4
    {128, 0, 128, 255}, // Purple for shape 5
    {0, 255, 255, 255}, // Cyan for shape 6
    {192, 192, 192, 255} // Gray for shape 7
};
// Tetromino shapes
vector<vector<vector<int>>> tetrominoShapes = {
    {{1, 1, 1, 1}},  // I
    {{1, 1}, {1, 1}}, // O
    {{0, 1, 1}, {1, 1, 0}}, // S
    {{1, 1, 0}, {0, 1, 1}}, // Z
    {{1, 1, 1}, {0, 1, 0}}, // T
    {{1, 1, 1}, {1, 0, 0}}, // L
    {{1, 1, 1}, {0, 0, 1}},  // J
    {{1, 1, 1}, {0, 0, 1}} //reverse L
};

struct Tetromino {
    vector<vector<int>> shape;
    int x, y;
    SDL_Color color;
    Tetromino(int type) {
        shape = tetrominoShapes[type];
        color=colors[type];
        x = GRID_WIDTH / 2 - shape[0].size() / 2;
        y = 0;
    }
    bool isValidPosition(int newX, int newY, const vector<vector<int>>& newShape, bool grid[GRID_HEIGHT][GRID_WIDTH]) {
        int shapeHeight = newShape.size();
        int shapeWidth = newShape[0].size();
        for (int i = 0; i < shapeHeight; i++) {
            for (int j = 0; j < shapeWidth; j++) {
                if (newShape[i][j] == 1) {
                    int gridX = newX + j;
                    int gridY = newY + i;
                    if (gridX < 0 || gridX >= GRID_WIDTH || gridY >= GRID_HEIGHT) {
                        return false;
                    }
                    if (grid[gridY][gridX]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void moveLeft(bool grid[GRID_HEIGHT][GRID_WIDTH]) {
        if (isValidPosition(x - 1, y, shape, grid)) {
            x--;
            //return true;
        }
        //return false;
    }

    void moveRight(bool grid[GRID_HEIGHT][GRID_WIDTH]) {
        if (isValidPosition(x + 1, y, shape, grid)) {
            x++;
            //return true;
        }
        //return false;
    }

    bool moveDown(bool grid[GRID_HEIGHT][GRID_WIDTH]) {
        if (isValidPosition(x, y + 1, shape, grid)) {
            y++;
            return true;
        }
        return false;
    }
    void rotate(bool grid[GRID_HEIGHT][GRID_WIDTH]) {
        int rows = shape.size();
        int cols = shape[0].size();
        vector<vector<int>> rotated(cols, vector<int>(rows, 0));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rotated[j][rows - 1 - i] = shape[i][j];
            }
        }

        if (isValidPosition(x, y, rotated, grid)) {
            shape = rotated;
            //return true;
        }
        //return false;
    }

    // Lock Tetromino into grid when it can't move down
    void lockToGrid(bool grid[GRID_HEIGHT][GRID_WIDTH]) {
        for (int i = 0; i < shape.size(); i++) {
            for (int j = 0; j < shape[i].size(); j++) {
                if (shape[i][j] == 1) {
                    grid[y + i][x + j] = true;
                }
            }
        }
    }
};
void drawTetromino(SDL_Renderer* renderer, Tetromino& tetromino) {
    SDL_SetRenderDrawColor(renderer, tetromino.color.r, tetromino.color.g, tetromino.color.b, 255); //draw color for tetromino

    for (int i = 0; i < tetromino.shape.size(); i++) {
        for (int j = 0; j < tetromino.shape[i].size(); j++) {
            if (tetromino.shape[i][j]) {
                SDL_Rect block = {
                    (tetromino.x + j) * BLOCK_SIZE + 250,
                    (tetromino.y + i) * BLOCK_SIZE + 50,
                    BLOCK_SIZE, BLOCK_SIZE
                };
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
}

#endif // TETROMINO_H_INCLUDED
