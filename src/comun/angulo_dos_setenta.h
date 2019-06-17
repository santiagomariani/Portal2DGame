#ifndef ANGULO_DOS_SETENTA_H
#define ANGULO_DOS_SETENTA_H

#include "angulo.h"
#include "Box2D/Box2D.h"

class AnguloDosSetenta : public Angulo{
public:
	AnguloDosSetenta();
	b2Vec2 obtenerPosPortal(b2Vec2& dif_choque) override ;
	b2Vec2 obtenerNormalPortal(b2Vec2& dif_choque) override ;
	b2PolygonShape obtenerTriangulo() override ;
	int getId() override ;
	~AnguloDosSetenta() = default;
};

#endif //ANGULO_DOS_SETENTA_H
