
#include "BloqueMetal.h"
#include "ids.h"
#include <iostream>
#include "cuerpo.h"
#include <cmath>

BloqueMetal::BloqueMetal(int identidad, Mundo& mundo, const b2Vec2& pos): id(identidad),
	Bloque(TAMANIO_BLOQUE * 2, TAMANIO_BLOQUE * 2) {

	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_staticBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo = mundo.agregarBody(cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;

	polygonShape.SetAsBox(TAMANIO_BLOQUE, TAMANIO_BLOQUE);
	cuerpo->CreateFixture(&myFixtureDef);
	cuerpo->SetUserData(this);
}

BloqueMetal::BloqueMetal(BloqueMetal&& otro) : 
			Bloque(TAMANIO_BLOQUE * 2, TAMANIO_BLOQUE * 2){
	if (this == &otro){
		return;
	}
	maxWidth = otro.maxWidth;
	maxHeight = otro.maxHeight;

	otro.maxWidth = 0;
	otro.maxHeight = 0;
	cuerpo = otro.cuerpo;
	cuerpo->SetUserData(this);
	otro.cuerpo = nullptr;
}

const b2Vec2& BloqueMetal::getPosition(){
	return cuerpo->GetPosition();
}
int BloqueMetal::getId(){
	return ID_METAL;
}

void BloqueMetal::recibirDisparo(Disparo* disparo) {
	b2Vec2 bloque = this->getPosition();
	b2Vec2 pos = disparo->getPosition();
	pos -= bloque;
	if (std::abs(pos.x) >= std::abs(pos.y)){
		pos.y = 0;
	} else {
		pos.x = 0;
	}
	pos *= TAMANIO_BLOQUE / pos.Length();
	pos += bloque;

	b2Vec2 normal = pos - bloque;
	normal.Normalize();

	disparo->crearPortal(pos, normal);
}

void BloqueMetal::empezarContacto(Cuerpo* otro){
	if (otro->getId() == ID_DISPARO){
		this->recibirDisparo((Disparo*)otro);
	}
}