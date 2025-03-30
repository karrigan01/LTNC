#ifndef MUSIC_BACKGROUND_H_INCLUDED
#define MUSIC_BACKGROUND_H_INCLUDED

#include <SDL_mixer.h>
#include <iostream>

using namespace std;
void playBackgroundMusic(const string& musicFile) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {//44100 hz, normal format, stereo
        cout << "SDL_mixer could not initialize! Error: " << Mix_GetError() << endl;
        return;
    }

    Mix_Music* bgMusic = Mix_LoadMUS(musicFile.c_str());
    if (!bgMusic) {
        cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
        return;
    }

    Mix_PlayMusic(bgMusic, -1);//loop infinite
}

void stopMusic() {
    Mix_HaltMusic();
    Mix_CloseAudio();
}

#endif // MUSIC_BACKGROUND_H_INCLUDED
