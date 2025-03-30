#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
int DROP_SPEED = 500; // milliseconds
// Button structure
struct Button {
    SDL_Rect rect;
    SDL_Color color;
    std::string text;
};


void renderButton(SDL_Renderer* renderer, TTF_Font* font, Button button) {
    SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g, button.color.b, 255);
    SDL_RenderFillRect(renderer, &button.rect);

    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, button.text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect = {
        button.rect.x + (button.rect.w - surface->w) / 2,
        button.rect.y + (button.rect.h - surface->h) / 2,
        surface->w,
        surface->h
    };

    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

bool isButtonClicked(Button button, int mouseX, int mouseY) {
    return (mouseX >= button.rect.x && mouseX <= button.rect.x + button.rect.w &&
            mouseY >= button.rect.y && mouseY <= button.rect.y + button.rect.h);
}
string difficulty[501];
void renderLevel(SDL_Renderer* renderer, TTF_Font* font){
    difficulty[200]="HARD", difficulty[400]="MEDIUM", difficulty[500]="EASY";
    SDL_Color white = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, ("Level: " + difficulty[DROP_SPEED]).c_str(), white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {20, 45, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
void showSettings(SDL_Renderer* renderer, TTF_Font* font) {
    bool inSettings = true;
    SDL_Event event;

    // Define buttons
    Button easyButton = {{150, 350, 180, 70}, {0, 255, 0, 255}, "Easy"};
    Button mediumButton = {{320, 350, 180, 70}, {255, 165, 0, 255}, "Medium"};
    Button hardButton = {{490, 350, 180, 70}, {255, 0, 0, 255}, "Hard"};

    while (inSettings) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        SDL_Color white = {255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Press ESC to return", white);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {20, 20, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        // Render difficulty buttons
        renderLevel(renderer,font);
        renderButton(renderer, font, easyButton);
        renderButton(renderer, font, mediumButton);
        renderButton(renderer, font, hardButton);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) exit(0);
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                inSettings = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (isButtonClicked(easyButton, x, y)) {
                    DROP_SPEED=500;
                }
                else if (isButtonClicked(mediumButton, x, y)) {
                    DROP_SPEED=400;
                }
                else if (isButtonClicked(hardButton, x, y)) {
                    DROP_SPEED=200;
                }
            }
        }
    }
}

#endif // SETTING_H_INCLUDED
