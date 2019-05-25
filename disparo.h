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
	bool listo;
public:
	Disparo(int identidad);
	void activar(Mundo& mundo, const b2Vec2& origen, const b2Vec2& destino);
	Disparo(Disparo&& otro);


	void setPortal(Portal* port);


	bool terminado();
	void terminar();
	void remover();
	Disparo& operator=(Disparo& otro);
	Disparo& operator=(Disparo&& otro);
	const b2Vec2& getPosition();
	double getAngle();
	int getId();
	void empezarContacto(Cuerpo* otro) {}
};

#endif //DISPARO_H
