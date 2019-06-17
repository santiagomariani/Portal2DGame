
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_mixer.h>
#include <sdl_exception.h>
#include "mixer.h"


Mixer::Mixer() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw SdlException("Error en la inicialización del mixer: %s\n",
                Mix_GetError());
    }
}

Mixer::~Mixer() {
    Mix_Quit();
}

