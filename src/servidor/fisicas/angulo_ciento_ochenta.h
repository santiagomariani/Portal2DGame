#ifndef ANGULO_CIENTO_OCHENTA_H
#define ANGULO_CIENTO_OCHENTA_H

#include "angulo.h"
#include "Box2D/Box2D.h"

class AnguloCientoOchenta : public Angulo{
public:
	AnguloCientoOchenta();
	b2Vec2 obtenerPosPortal(b2Vec2& dif_choque);
	b2Vec2 obtenerNormalPortal(b2Vec2& dif_choque);
	b2PolygonShape obtenerTriangulo();
	int getId();
	b2Vec2 obtenerVelocidadRebote(b2Vec2& vel_inicial) override;
	~AnguloCientoOchenta() = default;
};

#endif //ANGULO_CIENTO_OCHENTA_H
