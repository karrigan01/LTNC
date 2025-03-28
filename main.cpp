#define SDL_MAIN_HANDLED
#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
using namespace std;
bool grid[20][10];
void add_background_music(){
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) ;
    Mix_Music* bgMusic = Mix_LoadMUS("background.mp3");
    Mix_PlayMusic(bgMusic, -1);
    bool music = true;
    SDL_Event event;
    while (music) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { // Close window to stop music
                music = false;
            }
        }
        SDL_Delay(100);  // Prevent CPU overuse
    }

    // Cleanup
    Mix_FreeMusic(bgMusic);
    Mix_CloseAudio();
    SDL_Quit();
}
int main() {
    add_background_music();
}
