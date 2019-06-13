
#ifndef BLOQUEMETAL_H
#define BLOQUEMETAL_H

#include "Bloque.h"
#include "Box2D/Box2D.h"

class BloqueMetal : public Bloque{
    b2Body* cuerpo;
public:
    BloqueMetal(Mundo &mundo, const b2Vec2 &pos);
    BloqueMetal(BloqueMetal&& otro);
    void recibirDisparo(Disparo* disparo);
    uint8_t getId();
    const b2Vec2& getPosition();
    void empezarContacto(Cuerpo* otro);
};


#endif //BLOQUEMETAL_H