
#ifndef COLECCION_SPRITES_H
#define COLECCION_SPRITES_H


#include "renderizable.h"
#include "ventana.h"
#include "sprite.h"
#include <map>
#include <list>

class ColeccionSprites {
private:
    std::map<uint8_t, Sprite> sprites;
    std::list<Textura> texturas;
    void creacionSprites(Ventana &ventana);

public:
    explicit ColeccionSprites(Ventana &ventana);
    Sprite & obtenerSprite(uint8_t id);
};


#endif //COLECCION_SPRITES_H
