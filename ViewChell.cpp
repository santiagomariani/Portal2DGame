//
// Created by santi on 17/05/19.
//

#include <iostream>
#include "ViewChell.h"

#define FIRE_TO_REST 0

ViewChell::ViewChell(SdlWindow &window) {
    std::string shootingPath = "assets/chelltextures.png";
    chellTextures = std::move(SdlTexture(shootingPath, window));
    spritesCreation();
}

void ViewChell::spritesCreation() {
    // fire to rest
    sprites.emplace_back(143, 213, 1, 1104, 4, chellTextures);
    actualSprite = FIRE_TO_REST;
}

void ViewChell::render(SDL_Rect &dest,
        double angle,
        SDL_Point *center,
        SDL_RendererFlip flip) {
    Sprite &sprite = sprites.at(actualSprite);
    sprite.render(dest, angle, center, flip);
}
