#ifndef TORTA_H
#define TORTA_H

#include <cstdint>
#include "Box2D/Box2D.h"
#include "mundo.h"

class Torta :  public Cuerpo{
private:
	b2Body* cuerpo;
public:
	Torta(Mundo& mundo, const b2Vec2& pos);
	const b2Vec2& getPosition();
	uint8_t getId();
	void empezarContacto(Cuerpo* otro);
	~Torta() = default;
};


#endif
