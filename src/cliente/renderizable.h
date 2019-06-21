
#ifndef RENDERIZABLE_H
#define RENDERIZABLE_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

class Renderizable {
public:
    virtual void renderizar(SDL_Rect &destino,
                            double angulo = 0.0,
                            SDL_Point *centro = nullptr,
                            SDL_RendererFlip espejado = SDL_FLIP_NONE) = 0;
};


#endif //RENDERIZABLE_H
