//
// Created by santi on 24/05/19.
//

#include "CoordConverter.h"

CoordConverter::CoordConverter(int screenWidth, int screenHeight) :
    screenWidth(screenWidth), screenHeight(screenHeight) {
}

SDL_Rect CoordConverter::box2DToSDL(Cuerpo &cuerpo) {
    b2Vec2 position = cuerpo.getPosition();
    float maxWidth = cuerpo.getMaxWidth();
    float maxHeight = cuerpo.getMaxHeight();
    SDL_Rect res = {int((position.x) * CONVERSION) + (screenWidth / 2),
                    int((position.y) * CONVERSION * -1) + (screenHeight / 2),
                    int(maxWidth * CONVERSION),
                    int(maxHeight * CONVERSION)};
    res.x -= int((maxWidth / 2) * CONVERSION);
    res.y -= int((maxHeight / 2) * CONVERSION);
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
