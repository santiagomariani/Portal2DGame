//
// Created by santi on 08/06/19.
//

#ifndef INFOCUERPO_H
#define INFOCUERPO_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

struct InfoCuerpo {
public:
    uint8_t id;
    uint8_t estado;
    int32_t angulo;
    SDL_Rect dest;
    SDL_RendererFlip flip;
    uint8_t id_chell;
};


#endif //INFOCUERPO_H
