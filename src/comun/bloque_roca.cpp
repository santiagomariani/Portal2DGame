#include <iostream>
#include "bloque_roca.h"
#include "ids.h"
#include "Box2D/Box2D.h"
#include "config.h"

BloqueRoca::BloqueRoca(int identidad, Mundo& mundo, const b2Vec2& pos) : id(identidad),
	Bloque(config.tam_bloque * 2, config.tam_bloque * 2) {
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_staticBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo = mundo.agregarBody(cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;

	polygonShape.SetAsBox(config.tam_bloque, config.tam_bloque);
	cuerpo->CreateFixture(&myFixtureDef);
	cuerpo->SetUserData(this);
}
BloqueRoca::BloqueRoca(BloqueRoca&& otro) : Bloque(config.tam_bloque * 2, config.tam_bloque * 2) {
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

const b2Vec2& BloqueRoca::getPosition(){
	return cuerpo->GetPosition();
}

uint8_t BloqueRoca::getId(){
	return ID_BLOQUE_ROCA;
}

void BloqueRoca::recibirDisparo(Disparo* disparo) {
}

void BloqueRoca::empezarContacto(Cuerpo *otro) {
    if (otro->getId() == ID_DISPARO){
        this->recibirDisparo((Disparo*)otro);
    }
}

