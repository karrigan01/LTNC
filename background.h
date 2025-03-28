#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;
SDL_Texture* loadBackground(SDL_Renderer* renderer, const string& filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        cout << "Failed to load background image! Error: " << IMG_GetError() << endl;
    }
    return texture;
}

void renderBackground(SDL_Renderer* renderer, SDL_Texture* bgTexture) {
    if (bgTexture) {
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
    }
}

#endif
