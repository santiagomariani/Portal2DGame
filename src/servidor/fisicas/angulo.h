#ifndef ANGULO_H
#define ANGULO_H

#include "Box2D/Box2D.h"

class Angulo{
public:
	virtual b2Vec2 obtenerPosPortal(b2Vec2& dif_choque) = 0;
	virtual b2Vec2 obtenerNormalPortal(b2Vec2& dif_choque) = 0;
	virtual b2PolygonShape obtenerTriangulo() = 0;
	virtual int getId() = 0;
	virtual b2Vec2 obtenerVelocidadRebote(b2Vec2& vel_inicial) = 0;
};

#endif //ANGULO_H
