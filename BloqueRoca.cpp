#include "BloqueRoca.h"
#include "ids.h"
#include "Box2D/Box2D.h"
#define TAMANIO_BLOQUE_X 0.5f
#define TAMANIO_BLOQUE_Y 0.5f

BloqueRoca::BloqueRoca(Mundo& mundo, const b2Vec2& pos) :
	Bloque(TAMANIO_BLOQUE_X * 2, TAMANIO_BLOQUE_Y * 2) {
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_staticBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo = mundo.agregarBody(cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1; // hay que sacar esto.

	polygonShape.SetAsBox(TAMANIO_BLOQUE_X, TAMANIO_BLOQUE_Y);
	cuerpo->CreateFixture(&myFixtureDef);
	cuerpo->SetUserData(this);
}
BloqueRoca::BloqueRoca(BloqueRoca&& otro) : Bloque(TAMANIO_BLOQUE_X * 2, TAMANIO_BLOQUE_Y * 2) {
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
int BloqueRoca::getId(){
	return 1;
}

void BloqueRoca::recibirDisparo(Disparo* disparo){
	disparo->terminar();
}

void BloqueRoca::empezarContacto(Cuerpo *otro) {
    if (otro->getId() == ID_DISPARO){
        this->recibirDisparo((Disparo*)otro);
    }
}
