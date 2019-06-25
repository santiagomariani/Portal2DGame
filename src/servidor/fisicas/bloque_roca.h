#ifndef BLOQUE_ROCA_H
#define BLOQUE_ROCA_H

#include "Box2D/Box2D.h"
#include "bloque.h"
#include "mundo.h"
#include "cuerpo.h"
#include "disparo.h"

class BloqueRoca : public Bloque{
private:
	b2Body* cuerpo;
	int id;

public:
	BloqueRoca(int identidad, Mundo& mundo, const b2Vec2& posicion);
	BloqueRoca(BloqueRoca&& otro);
	// Devuelve el id asociado a la Roca.
	uint8_t getId();
	// Devuelve la posicion de la Roca.
	const b2Vec2& getPosition();
	void recibirDisparo(Disparo* disparo);
	void empezarContacto(Cuerpo* otro);
	b2Vec2 obtenerVelocidadRebote(b2Vec2& vel_inicial) override;
};

#endif //BLOQUE_ROCA_H