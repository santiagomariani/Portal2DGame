#ifndef ANGULO_NOVENTA_H
#define ANGULO_NOVENTA_H

#include "angulo.h"
#include "Box2D/Box2D.h"

class AnguloNoventa : public Angulo{
public:
	AnguloNoventa();
	b2Vec2 obtenerPosPortal(b2Vec2& dif_choque);
	b2Vec2 obtenerNormalPortal(b2Vec2& dif_choque);
	b2PolygonShape obtenerTriangulo();
	int getId();
	~AnguloNoventa() = default;
};

#endif
