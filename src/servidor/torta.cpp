#include <config.h>
#include "chell.h"
#include "torta.h"
#include "ids.h"

Torta::Torta(Mundo& mundo, const b2Vec2& pos):
            Cuerpo(config.tam_torta*2, config.tam_torta*2){
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_staticBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo = mundo.agregarBody(cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;

	polygonShape.SetAsBox(config.tam_torta, config.tam_torta);
	cuerpo->CreateFixture(&myFixtureDef);
	cuerpo->SetUserData(this);
}

const b2Vec2& Torta::getPosition(){
	return cuerpo->GetPosition();
}

uint8_t Torta::getId(){
	return ID_TORTA;
}

void Torta::empezarContacto(Cuerpo* otro){
	if (otro->getId() == ID_CHELL){
		((Chell*)otro)->ganar();
	}
}
