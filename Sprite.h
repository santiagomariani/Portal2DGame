//
// Created by santi on 18/05/19.
//

#ifndef TP4_SPRITE_H
#define TP4_SPRITE_H


#include "SdlTexture.h"
#include "SdlWindow.h"
#include "Renderable.h"

class Sprite : public Renderable {
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
    void render(SDL_Rect &dest,
                double angle,
                SDL_Point *center,
                SDL_RendererFlip flip) override;
    int getFrameWidth();
    int getFrameHeight();
    ~Sprite() = default;
};


#endif //TP4_SPRITE_H
