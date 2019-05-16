#include "roca.h"
#include "Box2D/Box2D.h"
#define TAMANIO_BLOQUE_X 0.5
#define TAMANIO_BLOQUE_Y 0.5

Roca::Roca(b2World& world, b2Vec2& pos){
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_staticBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo = world.CreateBody(&cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	polygonShape.SetAsBox(TAMANIO_BLOQUE_X, TAMANIO_BLOQUE_Y);
	cuerpo->CreateFixture(&myFixtureDef);
}
b2Vec2 Roca::getPosition(){
	return cuerpo->GetPosition();
}