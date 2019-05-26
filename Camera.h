//
// Created by santi on 24/05/19.
//

#ifndef CAMERA_H
#define CAMERA_H


#include <SDL2/SDL_rect.h>
#include "Renderable.h"

class Camera {
private:
    int screenWidth;
    int screenHeight;
    SDL_Rect camera;
public:
    Camera(int screenWidth, int screenHeight);
    void render(Renderable &renderable,
            SDL_Rect &dest,
            double angle = 0.0,
            SDL_Point *center = nullptr,
            SDL_RendererFlip flip = SDL_FLIP_NONE);
    void updateCamera(SDL_Rect &destChell);
    int getX();
    int getY();
};


#endif //CAMERA_H
