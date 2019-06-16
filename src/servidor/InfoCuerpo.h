#ifndef INFOCUERPO_H
#define INFOCUERPO_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

// Contiene informacion de un Cuerpo

struct InfoCuerpo {
public:
    uint8_t id;
    uint8_t estado;
    int32_t angulo;
    SDL_Rect dest;
    SDL_RendererFlip flip;
};


#endif //INFOCUERPO_H
