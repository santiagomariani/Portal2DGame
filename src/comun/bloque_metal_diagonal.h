
#ifndef BLOQUEMETALDIAGONAL_H
#define BLOQUEMETALDIAGONAL_H

#include "Bloque.h"
#include "angulo.h"
#include "Box2D/Box2D.h"

class BloqueMetalDiagonal : public Bloque{
    Angulo& angulo;
    b2Body* cuerpo;
    std::map<int, int> mapa_ids;
    void crearMapaIds();

public:
	// El angulo debe ser: 0, 90, 180 o 270
    BloqueMetalDiagonal(Mundo &mundo, const b2Vec2 &pos, Angulo& angulo);
    BloqueMetalDiagonal(BloqueMetalDiagonal&& otro);
    void recibirDisparo(Disparo* disparo);
    uint8_t getId();
    const b2Vec2& getPosition();
    void empezarContacto(Cuerpo* otro);
};


#endif //BLOQUEMETALDIAGONAL_H