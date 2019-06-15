//
// Created by santi on 17/05/19.
//

#ifndef TP4_VIEWCHELL_H
#define TP4_VIEWCHELL_H


#include <SDL2/SDL_system.h>
#include <vector>
#include <map>

#include "Textura.h"
#include "Sprite.h"

class ViewChell : public Renderable {
private:
    Textura chellTextures;
    std::map<uint8_t, Sprite> sprites;
    std::map<uint8_t, Sprite> sprites_transitorios;
    uint8_t estado_actual;
    bool renderizando_estado_transitorio;
    SDL_RendererFlip flip_transitorio;
    double angulo_transitorio;
    SDL_Point *centro_transitorio;
    void spritesCreation();
public:
    explicit ViewChell(Ventana &window, std::string nombre_archivo);
    ViewChell(ViewChell &&otro);
    ViewChell& operator=(ViewChell &&otro);
    void render(SDL_Rect &dest,
                     double angle,
                     SDL_Point *center,
                     SDL_RendererFlip flip) override;
    void cambiarEstado(uint8_t estado,
                       double angle = 0,
                       SDL_Point *center = nullptr,
                       SDL_RendererFlip flip = SDL_FLIP_NONE);
    ~ViewChell() = default;
};


#endif //TP4_VIEWCHELL_H
