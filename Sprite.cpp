//
// Created by santi on 18/05/19.
//

#include "Sprite.h"
#define SPEED 4

Sprite::Sprite(int frameWidth,
       int frameHeight,
       int x,
       int y,
       unsigned int numberFrames,
       SdlTexture &texture) :
       frameWidth(frameWidth),
       frameHeight(frameHeight),
       x(x),
       y(y),
       numberImages(numberFrames),
       texture(texture) {
    countedImages = 0;
    framesCounter = 0;
    srcArea.x = x;
    srcArea.y = y;
    srcArea.w = frameWidth;
    srcArea.h = frameHeight;
}

void Sprite::resetAnimation() {
    srcArea.x = x;
    srcArea.y = y;
    srcArea.w = frameWidth;
    srcArea.h = frameHeight;
    countedImages = 0;
}

void Sprite::render(SDL_Rect &dest,
                    double angle,
                    SDL_Point *center,
                    SDL_RendererFlip flip) {
    if (numberImages == 1) {
      texture.render(&srcArea, &dest, angle, center, flip);
      return;
    }
    framesCounter++;
    if (countedImages == numberImages) {
        resetAnimation();
    }
    texture.render(&srcArea, &dest, angle, center, flip);
    if (framesCounter == SPEED) {
        countedImages++;
        framesCounter = 0;
        srcArea.x += frameWidth + 1;
        if (srcArea.x + srcArea.w >= texture.getWidth()) {
            srcArea.x = x;
            srcArea.y += frameHeight + 1;
        }
    }
}

int Sprite::getFrameWidth() {
    return frameWidth;
}

int Sprite::getFrameHeight() {
    return frameHeight;
}

bool Sprite::finalizoAnimacion() {
    return countedImages == numberImages;
}
