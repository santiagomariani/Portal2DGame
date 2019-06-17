//
// Created by santi on 08/06/19.
//

#ifndef INFO_CUERPO_H
#define INFO_CUERPO_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

struct InfoCuerpo {
public:
    uint8_t id;
    uint8_t estado;
    int32_t angulo;
    SDL_Rect destino;
    SDL_RendererFlip espejado;
};


#endif //INFO_CUERPO_H
