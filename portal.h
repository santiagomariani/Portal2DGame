#ifndef PORTAL_H
#define PORTAL_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "cuerpo.h"

class Portal : public Cuerpo {
	int id;
	Portal* hermano;
	b2Body* cuerpo;
	float orientacion;
public:
	Portal(int identidad);

	void conectar(Portal* otro);
	void activar(Mundo& mundo, const b2Vec2& pos, const b2Vec2& normal);
	int getId();
	const b2Vec2& getPosition();
	void teletransportar(b2Body* otro);
	void expulsar(b2Body* otro, float orientacion_otro);
	float getAnguloSalida();
	float getAnguloEntrada();



	void empezarContacto(Cuerpo* otro) {}

};

#endif //PORTAL_H
