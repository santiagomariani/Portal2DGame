#include "roca.h"
#include "Box2D/Box2D.h"
#define TAMANIO_BLOQUE_X 0.5
#define TAMANIO_BLOQUE_Y 0.5

Roca::Roca(Mundo& mundo, const b2Vec2& pos){
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_staticBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo = mundo.agregarBody(cuerpo_def);
	//cuerpo = world.CreateBody(&cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	polygonShape.SetAsBox(TAMANIO_BLOQUE_X, TAMANIO_BLOQUE_Y);
	cuerpo->CreateFixture(&myFixtureDef);
	cuerpo->SetUserData(this);
}
Roca::Roca(Roca&& otro){
	if (this == &otro){
		return;
	}
	cuerpo = otro.cuerpo;
	cuerpo->SetUserData(this);
	otro.cuerpo = nullptr;
}
const b2Vec2& Roca::getPosition(){
	return cuerpo->GetPosition();
}
int Roca::getId(){
	return 1;
}
