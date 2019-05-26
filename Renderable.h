//
// Created by santi on 24/05/19.
//

#ifndef RENDERABLE_H
#define RENDERABLE_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

class Renderable {
public:
    virtual void render(SDL_Rect &dest,
                     double angle = 0.0,
                     SDL_Point *center = nullptr,
                     SDL_RendererFlip flip = SDL_FLIP_NONE) = 0;
};


#endif //RENDERABLE_H
