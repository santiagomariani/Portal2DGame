#ifndef PORTAL_H
#define PORTAL_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "chell.h"

class Portal{
	Portal* hermano;
	b2Body* cuerpo;
	float orientacion;
public:
	Portal(Mundo& mundo, const b2Vec2& pos, const b2Vec2& normal);
	void teletransportar(Chell* chell);
	void expulsar(Chell* chell, float orientacion_otro);
	float getAnguloSalida();
	float getAnguloEntrada();

};

#endif //PORTAL_H
