#ifndef ANGULO_CIENTOOCHENTA_H
#define ANGULO_CIENTOOCHENTA_H

#include "angulo.h"
#include "Box2D/Box2D.h"

class AnguloCientoOchenta : public Angulo{
public:
	AnguloCientoOchenta();
	b2Vec2 obtenerPosPortal(b2Vec2& dif_choque);
	b2Vec2 obtenerNormalPortal(b2Vec2& dif_choque);
	b2PolygonShape obtenerTriangulo();
	int getId();
	~AnguloCientoOchenta() = default;
};

#endif
