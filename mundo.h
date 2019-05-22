#ifndef MUNDO_H
#define MUNDO_H

#include <map>
#include "Box2D/Box2D.h"

class Mundo{
	b2World mundo;
public:
	Mundo(const b2Vec2& gravedad);

	void setContactListener(b2ContactListener& listener);

	b2Body* agregarBody(b2BodyDef& cuerpo_def);
	void destruirBody(b2Body* body);
	void actualizar();
	b2Body* obtenerBodies();
	
};

#endif //MUNDO_H
