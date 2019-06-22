#ifndef ANGULO_CERO_H
#define ANGULO_CERO_H

#include "angulo.h"
#include "Box2D/Box2D.h"

class AnguloCero : public Angulo{
public:
	AnguloCero();
	b2Vec2 obtenerPosPortal(b2Vec2& dif_choque);
	b2Vec2 obtenerNormalPortal(b2Vec2& dif_choque);
	b2PolygonShape obtenerTriangulo();
	b2Vec2 obtenerVelocidadRebote(b2Vec2& vel_inicial);
	int getId();
	~AnguloCero() = default;
};

#endif
