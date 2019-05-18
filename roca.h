#ifndef ROCA_H
#define ROCA_H
#include "Box2D/Box2D.h"

class Roca{
	b2Body* cuerpo;
public:
	Roca(b2World& world, const b2Vec2& posicion);
	Roca(Roca&& otro);
	b2Vec2 getPosition();
};

#endif //ROCA_H