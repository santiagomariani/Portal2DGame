
#ifndef UNTITLED_BLOQUEMETAL_H
#define UNTITLED_BLOQUEMETAL_H

#include "Bloque.h"
#include "Box2D/Box2D.h"

class BloqueMetal : public Bloque{
    b2Body* cuerpo;
    int id;
public:
    BloqueMetal(int identidad, Mundo& mundo, const b2Vec2& pos);
    void recibirDisparo(Disparo* disparo);
    int getId();
    const b2Vec2& getPosition();
    void empezarContacto(Cuerpo* otro);
};


#endif //UNTITLED_BLOQUEMETAL_H
