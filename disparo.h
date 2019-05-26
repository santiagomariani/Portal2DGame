#ifndef DISPARO_H
#define DISPARO_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "cuerpo.h"
#include "portal.h"

class Disparo : public Cuerpo{
	int id;
	b2Body* cuerpo;
	Portal* portal;
	Mundo& mundo;
public:
	Disparo(int identidad, Mundo& mundo);
	void activar(const b2Vec2& origen, const b2Vec2& destino);
	Disparo(Disparo&& otro);
	void setPortal(Portal* port);
	void desactivar();
	Disparo& operator=(Disparo&& otro);
	const b2Vec2& getPosition();
	double getAngle();
	int getId();
	void empezarContacto(Cuerpo* otro) {}

    void crearPortal(b2Vec2& pos, b2Vec2& normal);

    void terminar();
};

#endif //DISPARO_H
