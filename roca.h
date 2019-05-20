#ifndef ROCA_H
#define ROCA_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "cuerpo.h"

class Roca : public Cuerpo{
	b2Body* cuerpo;
public:
	Roca(Mundo& mundo, const b2Vec2& posicion);
	Roca(Roca&& otro);
	int getId();
	const b2Vec2& getPosition();
	float getWidth();
	float getHeight();
};

#endif //ROCA_H