#ifndef BLOQUE_ROCA_H
#define BLOQUE_ROCA_H

#include "Box2D/Box2D.h"
#include "Bloque.h"
#include "mundo.h"
#include "cuerpo.h"
#include "disparo.h"

class BloqueRoca : public Bloque{
	b2Body* cuerpo;
	int id;
public:
	BloqueRoca(int identidad, Mundo& mundo, const b2Vec2& posicion);
	BloqueRoca(BloqueRoca&& otro);
	void recibirDisparo(Disparo* disparo);
	uint8_t getId();
	const b2Vec2& getPosition();
	void empezarContacto(Cuerpo* otro);
};

#endif //BLOQUE_ROCA_H