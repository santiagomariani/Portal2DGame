#ifndef DISPARO_H
#define DISPARO_H
#include "Box2D/Box2D.h"

class Disparo{
	b2Body* circle_body;
public:
	Disparo(b2World& world, const b2Vec2& origen, const b2Vec2& destino);
	b2Vec2 getPosition();
	float32 getAngle();
};

#endif //DISPARO_H