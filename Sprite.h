//
// Created by santi on 18/05/19.
//

#ifndef TP4_SPRITE_H
#define TP4_SPRITE_H


#include "SdlTexture.h"
#include "SdlWindow.h"

class Sprite {
private:
    int frameWidth;
    int frameHeight;
    int x, y;
    int numberImages;
    int countedImages;
    int framesCounter;
    SDL_Rect srcArea;
    SdlTexture &texture;
public:
    Sprite(int frameWidth,
            int frameHeight,
            int x,
            int y,
            unsigned int numberFrames,
            SdlTexture &texture);
    void resetAnimation();
    void renderFrame(SDL_Rect &dest,
         double angle = 0.0,
         SDL_Point *center = nullptr,
         SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getFrameWidth();
    int getFrameHeight();
    ~Sprite() = default;
};


#endif //TP4_SPRITE_H
