//
// Created by santi on 24/05/19.
//

#include "Camera.h"

Camera::Camera(int screenWidth, int screenHeight, SdlTexture &bg) :
    screenWidth(screenWidth), screenHeight(screenHeight), bg(bg){
    camera.x = 0;
    camera.y = 0;
    camera.w = screenWidth;
    camera.h = screenHeight;
}

void Camera::render(Renderable &renderable,
        SDL_Rect &dest,
        double angle,
        SDL_Point *center,
        SDL_RendererFlip flip) {
    if ((dest.x >= (camera.x + camera.w)) || ((dest.x + dest.w - 1) < camera.x)) {
        return;
    } else if ((dest.y >= (camera.y + camera.h)) || ((dest.y + dest.h - 1) < camera.y)) {
        return;
    }
    SDL_Rect copia = dest;
    copia.x = dest.x - camera.x;
    copia.y = dest.y - camera.y;
    renderable.render(copia, angle, center, flip);
}
void Camera::updateCamera(SDL_Rect &destChell) {
    int chellCenteredX = destChell.x + (destChell.w / 2);
    int chellCenteredY = destChell.y + (destChell.h / 2);
    camera.x = (chellCenteredX - (screenWidth / 2));
    camera.y = (chellCenteredY - (screenHeight / 2));

    /*
    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > screenWidth - camera.w) {
        camera.x = screenWidth - camera.w;
    }
    if (camera.y > screenHeight - camera.h) {
        camera.y = screenHeight - camera.h;
    }
    */
}

int Camera::getX() {
    return camera.x;
}

int Camera::getY() {
    return camera.y;
}

void Camera::renderBg() {
    SDL_Rect dest = {0,
                     0,
                     camera.w,
                     camera.h};
    bg.render(nullptr, &dest);
}
