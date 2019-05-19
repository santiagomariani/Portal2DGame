#ifndef DISPARO_H
#define DISPARO_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "cuerpo.h"

class Disparo : public Cuerpo{
	b2Body* cuerpo;
public:
	Disparo();
	void activar(Mundo& mundo, const b2Vec2& origen, const b2Vec2& destino);
	Disparo(Disparo&& otro);
	Disparo& operator=(Disparo& otro);
	Disparo& operator=(Disparo&& otro);
	const b2Vec2& getPosition();
	float32 getAngle();
	int getId();
};

#endif //DISPARO_H