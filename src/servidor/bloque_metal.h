
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
    // Devuelve la velocidad final del objeto que rebote con el bloque
    b2Vec2 obtenerVelocidadRebote(b2Vec2& vel_inicial);
};


#endif //BLOQUE_METAL_H
