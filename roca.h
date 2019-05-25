#ifndef ROCA_H
#define ROCA_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "cuerpo.h"
#include "disparo.h"

class Roca : public Cuerpo{
	b2Body* cuerpo;
public:
	Roca(Mundo& mundo, const b2Vec2& posicion);
	Roca(Roca&& otro);
	void recibirDisparo(Disparo* disparo);
	int getId();
	const b2Vec2& getPosition();
	float getWidth();
	float getHeight();



	void empezarContacto(Cuerpo* otro) {}
	
};

#endif //ROCA_H