//
// Created by santi on 24/05/19.
//

#ifndef CAMERA_H
#define CAMERA_H


#include <SDL2/SDL_rect.h>
#include "Renderable.h"
#include "Textura.h"
#include "SonidosChell.h"

class Camera {
private:
    int screenWidth;
    int screenHeight;
    SDL_Rect camera;
    Textura &bg; // background.
    bool dentroDeCamara(SDL_Rect &dest);
public:
    Camera(int screenWidth, int screenHeight, Textura &bg);
    void render(Renderable &renderable,
            SDL_Rect &dest,
            double angle = 0.0,
            SDL_Point *center = nullptr,
            SDL_RendererFlip flip = SDL_FLIP_NONE);
    void renderBg();
    void reproducirSonidoChell(SonidosChell &sonidos_chell, SDL_Rect &dest, uint8_t estado);
    void updateCamera(SDL_Rect &destChell);
    int getX();
    int getY();
};


#endif //CAMERA_H
