
#ifndef BLOQUE_METAL_H
#define BLOQUE_METAL_H

#include "bloque.h"
#include "Box2D/Box2D.h"

class BloqueMetal : public Bloque{
private:
    b2Body* cuerpo;

public:
    BloqueMetal(Mundo &mundo, const b2Vec2 &pos);
    BloqueMetal(BloqueMetal&& otro);
    // Devuelve el id asociado con el Bloque de metal.
    uint8_t getId();
    // Devuelve la posicion asociada al Bloque de metal.
    const b2Vec2& getPosition();
    // Crea el portal en el lado que corresponda del Bloque.
    void recibirDisparo(Disparo* disparo);
    void empezarContacto(Cuerpo* otro);
};


#endif //BLOQUE_METAL_H
