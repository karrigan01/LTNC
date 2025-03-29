#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>

bool showMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* menuTexture) {
    bool inMenu = true;
    SDL_Event event;

    while (inMenu) {
        // Render the menu background image
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);

        // Render text
        SDL_Color white = {255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Press ENTER to Start", white);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {SCREEN_WIDTH / 2 - surface->w / 2, SCREEN_HEIGHT / 2 - surface->h / 2, surface->w, surface->h};

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(textTexture);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false; // Exit game
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                inMenu = false; // Start game
            }
        }
    }
    return true;
}

#endif // MENU_H_INCLUDED
