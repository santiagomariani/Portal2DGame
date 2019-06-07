//
// Created by santi on 17/05/19.
//

#ifndef TP4_VIEWCHELL_H
#define TP4_VIEWCHELL_H


#include <SDL2/SDL_system.h>
#include <vector>

#include "SdlTexture.h"
#include "Sprite.h"

class ViewChell : public Renderable {
private:
    SdlTexture chellTextures;
    std::vector<Sprite> sprites;
    uint8_t estado_actual;
    void spritesCreation();
public:
    explicit ViewChell(SdlWindow &window);
    void cambiarEstado(uint8_t estado);
    void render(SDL_Rect &dest,
                     double angle,
                     SDL_Point *center,
                     SDL_RendererFlip flip) override;
    ~ViewChell() = default;
};


#endif //TP4_VIEWCHELL_H
