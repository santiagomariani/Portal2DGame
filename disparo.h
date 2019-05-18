#ifndef DISPARO_H
#define DISPARO_H
#include "Box2D/Box2D.h"
#include "mundo.h"

class Disparo{
	b2Body* cuerpo;
public:
	Disparo(Mundo& mundo, const b2Vec2& origen, const b2Vec2& destino);
	Disparo(Disparo&& otro);
	b2Vec2 getPosition();
	float32 getAngle();
};

#endif //DISPARO_H