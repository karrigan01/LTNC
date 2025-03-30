#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "setting.h"

// Menu function
bool showMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* menuTexture) {
    bool inMenu = true;
    SDL_Event event;

    // Define buttons
    Button startButton = {{300, 300, 200, 50}, {0, 128, 255, 255}, "Start"};
    Button settingsButton = {{300, 400, 200, 50}, {128, 128, 128, 255}, "Settings"};

    while (inMenu) {
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);

        // Render "TETRIS" Logo
        TTF_Font* fontt = TTF_OpenFont("Arial Bold.ttf", 72);//Make logo bigger
        SDL_Color yellow = {255, 255, 0}; // Yellow for classic Tetris look
        SDL_Surface* logoSurface = TTF_RenderText_Solid(fontt, "TETRIS", yellow);
        SDL_Texture* logoTexture = SDL_CreateTextureFromSurface(renderer, logoSurface);
        SDL_Rect logoRect = {270, 200, logoSurface->w, logoSurface->h};

        SDL_RenderCopy(renderer, logoTexture, NULL, &logoRect);
        SDL_FreeSurface(logoSurface);
        SDL_DestroyTexture(logoTexture);

        // Render buttons
        renderButton(renderer, font, startButton);
        renderButton(renderer, font, settingsButton);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false; // Exit game
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (isButtonClicked(startButton, x, y)) {
                    inMenu = false; // Start game
                }
                if (isButtonClicked(settingsButton, x, y)) {
                    // Open settings (implement later)
                    showSettings(renderer,font);

                }
            }
        }
    }
    return true;
}

#endif // MENU_H_INCLUDED
