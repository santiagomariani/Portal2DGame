#include "portal.h"
#include "chell.h"
#include "ids.h"
#include <math.h>
#include "Box2D/Box2D.h"
#include <iostream>
#define TAMANIO_PORTAL_X 0.5
#define TAMANIO_PORTAL_Y 0.05

#define PI 3.14159265


Portal::Portal(int identidad, Mundo& mundo) : id(identidad), mundo(mundo), pos(0, 0), normal(0, 0){
	orientacion = 0.0f;
	hermano = nullptr;
	cuerpo = nullptr;
}

void Portal::activar(){
	if (cuerpo){
		mundo.destruirBody(cuerpo);
		cuerpo = nullptr;
	}
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_staticBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo = mundo.agregarBody(cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	orientacion = atan2(normal.y, normal.x);
	if (orientacion < 0){
		orientacion += 2 * PI;
	}
	polygonShape.SetAsBox(TAMANIO_PORTAL_X, TAMANIO_PORTAL_Y, (2 * (normal + pos)) , orientacion);
	cuerpo->CreateFixture(&myFixtureDef);
	cuerpo->SetUserData(this);
}

void Portal::conectar(Portal* otro){
	hermano = otro;
}

float Portal::getAnguloSalida(){
	return orientacion;
}

int Portal::getId(){
	return id;
}

const b2Vec2& Portal::getPosition(){
	return cuerpo->GetPosition();
}

float Portal::getAnguloEntrada(){
	if (orientacion - PI < 0){
		return orientacion + PI;
	}
	return orientacion - PI;
}

void Portal::expulsar(b2Body* otro, float orientacion_otro){
	if (!cuerpo)
		return;
	float nuevo_ang = getAnguloSalida() - orientacion_otro;
	b2Rot rotador(nuevo_ang);
	b2Vec2 vel = otro->GetLinearVelocity();
	b2Vec2 nueva_vel = b2Mul(rotador, vel);
	otro->SetLinearVelocity(nueva_vel);
	otro->SetTransform((cuerpo->GetPosition() + (0.2f * normal)), 0.0f);
}

void Portal::teletransportar(b2Body* otro){
	if (!cuerpo)
		return;
	hermano->expulsar(otro, getAnguloEntrada());
}

void Portal::establecer(b2Vec2& posicion, b2Vec2& normal_entrada) {
	pos.x = posicion.x;
	pos.y = posicion.y;
	normal.x = normal_entrada.x;
	normal.y = normal_entrada.y;
}
Portal::Portal(Portal&& otro) : mundo(otro.mundo){
	pos = otro.pos;
	normal = otro.normal;
	id = otro.id;
	cuerpo = otro.cuerpo;
	otro.cuerpo = nullptr;
	orientacion = otro.orientacion;
	if (cuerpo){
		cuerpo->SetUserData(this);
	}
}
void Portal::empezarContacto(Cuerpo* otro){
	switch (otro->getId()){
		case(ID_CHELL):
			std::cout << "Me estan tocando UwU (* ^ . ^ *)\n";
			teletransportar(otro->getBody());
	}
}

