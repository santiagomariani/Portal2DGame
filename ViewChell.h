//
// Created by santi on 17/05/19.
//

#ifndef TP4_VIEWCHELL_H
#define TP4_VIEWCHELL_H


#include <SDL2/SDL_system.h>
#include <vector>

#include "SdlTexture.h"
#include "Sprite.h"

class ViewChell {
private:
    SdlTexture chellTextures;
    std::vector<Sprite> sprites;
    int actualSprite;
    void spritesCreation();
public:
    ViewChell(SdlWindow &window);
    void render(float x, float y, float xCam, float yCam);
    ~ViewChell() = default;
};


#endif //TP4_VIEWCHELL_H
