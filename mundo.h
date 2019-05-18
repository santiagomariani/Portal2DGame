#ifndef MUNDO_H
#define MUNDO_H

#include <map>
#include "Box2D/Box2D.h"
#include "chell.h"
#include "roca.h"
#include "disparo.h"
#include <vector>

class Mundo{
	b2World mundo;
public:
	Mundo(const b2Vec2& gravedad);

	b2Body* agregarBody(b2BodyDef& cuerpo_def);
	void actualizar();
	
};

#endif //MUNDO_H
