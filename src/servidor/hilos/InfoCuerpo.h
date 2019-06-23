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
    SDL_Rect destino;
    SDL_RendererFlip espejado;
};


#endif //INFO_CUERPO_H
