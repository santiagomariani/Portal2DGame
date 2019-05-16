#include "chell.h"
#include "Box2D/Box2D.h"
#define TAMANIO_CHELL_X 0.25
#define TAMANIO_CHELL_Y 0.75

Chell::Chell(b2World& world, b2Vec2& pos){
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_dynamicBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo = world.CreateBody(&cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	polygonShape.SetAsBox(TAMANIO_CHELL_X, TAMANIO_CHELL_Y);
	cuerpo->CreateFixture(&myFixtureDef);
}
void Chell::saltar(){
	b2Vec2 vel = cuerpo->GetLinearVelocity();
	if (vel.y == 0){
		vel.y = 10;
		cuerpo->SetLinearVelocity(vel);
	}
}
void Chell::moverDerecha(){
	b2Vec2 vel = cuerpo->GetLinearVelocity();
	vel.x = 5;
	cuerpo->SetLinearVelocity(vel);
}
void Chell::moverIzquierda(){
	b2Vec2 vel = cuerpo->GetLinearVelocity();
	vel.x = -5;
	cuerpo->SetLinearVelocity(vel);
}
b2Vec2 Chell::getPosition(){
	return cuerpo->GetPosition();
}