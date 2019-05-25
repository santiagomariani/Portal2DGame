#ifndef CUERPO_H
#define CUERPO_H

#include "Box2D/Box2D.h"

class Cuerpo{
public:
	Cuerpo() {};
	virtual int getId() = 0;
	virtual const b2Vec2& getPosition() = 0;
	virtual void empezarContacto(Cuerpo* otro) = 0;
	~Cuerpo() {};
};

#endif

