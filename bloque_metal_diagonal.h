
#ifndef BLOQUEMETALDIAGONAL_H
#define BLOQUEMETALDIAGONAL_H

#include "Bloque.h"
#include "angulo.h"
#include "Box2D/Box2D.h"

class BloqueMetalDiagonal : public Bloque{
    b2Body* cuerpo;
    int id;
    Angulo& angulo;
    std::map<int, int> mapa_ids;
    void crearMapaIds();

public:
	// El angulo debe ser: 0, 90, 180 o 270
    BloqueMetalDiagonal(int identidad, Mundo& mundo, const b2Vec2& pos, Angulo& angulo);
    BloqueMetalDiagonal(BloqueMetalDiagonal&& otro);
    void recibirDisparo(Disparo* disparo);
    uint8_t getId();
    const b2Vec2& getPosition();
    void empezarContacto(Cuerpo* otro);
};


#endif //BLOQUEMETALDIAGONAL_H