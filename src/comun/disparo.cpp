#include <iostream>
#include "disparo.h"
#include "ids.h"
#include "Box2D/Box2D.h"
#include <math.h>
#include "config.h"

#define PI 3.14159265

#define DENSIDAD_RAYO 1

Disparo::Disparo(int identidad, Mundo& mundo) : 
			id(identidad), mundo(mundo),
			Cuerpo(config.radio_disparo * 2, config.radio_disparo * 2) {
	cuerpo = nullptr;
	portal = nullptr;
}

void Disparo::activar(const b2Vec2& origen, const b2Vec2& destino){
	if (cuerpo){
		mundo.destruirBody(cuerpo);
		cuerpo = nullptr;
	}
	b2BodyDef circle_body_def;
	circle_body_def.type = b2_dynamicBody;
	circle_body_def.position.Set(origen.x, origen.y);
	circle_body_def.fixedRotation = true;
	circle_body_def.bullet = true;
	cuerpo = mundo.agregarBody(circle_body_def);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = config.radio_disparo;
	b2FixtureDef circle_fixture_def;
	circle_fixture_def.shape = &circleShape;
	circle_fixture_def.density = DENSIDAD_RAYO;
	circle_fixture_def.isSensor = true; // no choca con nada pero se pueden detectar
										// las colisiones
	cuerpo->CreateFixture(&circle_fixture_def);

	b2Vec2 vel = destino;
	vel -= origen;
	vel.Normalize();
	vel *= config.velocidad_disparo;
	cuerpo->SetGravityScale(0);
	cuerpo->SetLinearVelocity(vel);
	cuerpo->SetUserData(this);
}

Disparo::Disparo(Disparo&& otro) : 
		mundo(otro.mundo),
		Cuerpo(config.radio_disparo * 2, config.radio_disparo * 2) {
	if (this == &otro){
		return;
	}
	maxWidth = otro.maxWidth;
	maxHeight = otro.maxHeight;
	cuerpo = otro.cuerpo;
	portal = otro.portal;
	id = otro.id;
	otro.maxWidth = 0;
	otro.maxHeight = 0;
	otro.cuerpo = nullptr;
	if (cuerpo){
		cuerpo->SetUserData(this);
	}
}

void Disparo::setPortal(Portal* port){
	portal = port;
}

void Disparo::crearPortal(b2Vec2& pos, b2Vec2& normal){
	portal->establecer(pos, normal);
	this->mundo.agregarPortal(portal);
}

const b2Vec2& Disparo::getPosition(){
	return cuerpo->GetPosition();
}
int32_t Disparo::getAngle(){
	b2Vec2 vel = cuerpo->GetLinearVelocity();
	float angulo = atan2(vel.y, vel.x);
	return (uint32_t)(angulo * 180/PI);
}
uint8_t Disparo::getId(){
	return ID_DISPARO;
}

Disparo& Disparo::operator=(Disparo&& otro){
	if (this == &otro){
		return *this;
	}

	maxWidth = otro.maxWidth;
	maxHeight = otro.maxHeight;
	cuerpo = otro.cuerpo;
	mundo = std::move(otro.mundo);
	portal = otro.portal;
	id = otro.id;
	otro.maxWidth = 0;
	otro.maxHeight = 0;
	otro.cuerpo = nullptr;
	cuerpo->SetUserData(this);
	return *this;
}

void Disparo::desactivar(){
	if (cuerpo){
		mundo.destruirBody(cuerpo);
		cuerpo = nullptr;
	}
}

void Disparo::terminar() {
	this->mundo.agregarCuerpoADestruir(this);
}


void Disparo::empezarContacto(Cuerpo* otro){
	int id_otro = otro->getId();
	if (id_otro == ID_BLOQUE_ROCA || id_otro == ID_BLOQUE_METAL || 
		id_otro == ID_COMPUERTA_CERRADA || id_otro == ID_BOTON_APAGADO ||
		id_otro == ID_BOTON_PRENDIDO || id_otro == ID_EMISORARRIBA ||
		id_otro == ID_EMISORDERECHA || id_otro == ID_EMISORIZQUIERDA ||
		id_otro == ID_EMISORABAJO || id_otro == ID_BARRAENERGIA){
		terminar();
	}
}
