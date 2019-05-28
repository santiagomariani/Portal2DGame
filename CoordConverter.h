//
// Created by santi on 24/05/19.
//

#ifndef COORDCONVERTER_H
#define COORDCONVERTER_H


#include <SDL2/SDL_rect.h>
#include <Box2D/Common/b2Math.h>
#include "cuerpo.h"
#include "Camera.h"

class CoordConverter {
private:
    const int CONVERSION = 100;
    int screenWidth, screenHeight;
public:
    CoordConverter(int screenWidth, int screenHeight);
    SDL_Rect box2DToSDL(Cuerpo &cuerpo);
    b2Vec2 sdlToBox2D(int x, int y, Camera &camera);
};


#endif //COORDCONVERTER_H