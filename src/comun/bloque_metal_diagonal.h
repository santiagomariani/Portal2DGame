
#ifndef BLOQUE_METAL_DIAGONAL_H
#define BLOQUE_METAL_DIAGONAL_H

#include "bloque.h"
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
    // Crea el portal en el lado correspondiente.
    void recibirDisparo(Disparo* disparo);
    // Devuelve el id asociado con el Bloque diagonal.
    uint8_t getId();
    // Devuelve la posicion del Bloque diagonal.
    const b2Vec2& getPosition();
    void empezarContacto(Cuerpo* otro);
};


#endif //BLOQUE_METAL_DIAGONAL_H