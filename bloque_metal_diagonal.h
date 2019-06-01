
#ifndef BLOQUEMETALDIAGONAL_H
#define BLOQUEMETALDIAGONAL_H

#include "Bloque.h"
#include "Box2D/Box2D.h"

class BloqueMetalDiagonal : public Bloque{
    b2Body* cuerpo;
    int id;
    float angulo;
public:
    BloqueMetalDiagonal(int identidad, Mundo& mundo, const b2Vec2& pos);
    BloqueMetalDiagonal(BloqueMetaDiagonall&& otro);
    void recibirDisparo(Disparo* disparo);
    int getId();
    const b2Vec2& getPosition();
    void empezarContacto(Cuerpo* otro);
};


#endif //BLOQUEMETALDIAGONAL_H