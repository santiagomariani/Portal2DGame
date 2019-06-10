//
// Created by santi on 24/05/19.
//
#include <iostream>
#include "CoordConverter.h"

CoordConverter::CoordConverter(int screenWidth, int screenHeight) :
    screenWidth(screenWidth), screenHeight(screenHeight) {
}

SDL_Rect CoordConverter::box2DToSDL(b2Vec2 posicion,
        float32 ancho_maximo,
        float32 alto_maximo) {
    SDL_Rect res = {int((posicion.x) * CONVERSION) + (screenWidth / 2),
                    int((posicion.y) * CONVERSION * -1) + (screenHeight / 2),
                    int(ancho_maximo * CONVERSION),
                    int(alto_maximo* CONVERSION)};
    res.x -= int((ancho_maximo / 2) * CONVERSION);
    res.y -= int((alto_maximo / 2) * CONVERSION);
    return res;
    /*
    int posX = (position.x * CONVERSION) + (screenWidth / 2);
    int posY = (position.y * CONVERSION * -1) + (screenHeight / 2);
    */
}

b2Vec2 CoordConverter::sdlToBox2D(int x, int y, Camera &camera) {
    b2Vec2 res;
    res.x = (x + camera.getX() - ((float)screenWidth / 2)) / CONVERSION;
    res.y = ((y + camera.getY() - ((float)screenHeight / 2)) / CONVERSION) * -1;
    return res;
}
