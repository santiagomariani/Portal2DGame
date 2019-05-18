#ifndef ROCA_H
#define ROCA_H
#include "Box2D/Box2D.h"
#include "mundo.h"

class Roca{
	b2Body* cuerpo;
public:
	Roca(Mundo& mundo, const b2Vec2& posicion);
	Roca(Roca&& otro);
	b2Vec2 getPosition();
};

#endif //ROCA_H