#include <iostream>
#include "chell.h"
#include "Box2D/Box2D.h"
#define TAMANIO_CHELL_X 0.25
#define TAMANIO_CHELL_Y 0.75
#define CAMINAR 5
#define SALTAR 25

Chell::Chell(b2World& world, b2Vec2& pos){
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_dynamicBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo_def.fixedRotation = true;
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
void Chell::mover(const Uint8 *state){
	b2Vec2 vel = cuerpo->GetLinearVelocity();
	vel.x = CAMINAR * state[SDL_SCANCODE_RIGHT] + -CAMINAR * state[SDL_SCANCODE_LEFT];
	if (vel.y == 0)
		vel.y = SALTAR * state[SDL_SCANCODE_UP];
	cuerpo->SetLinearVelocity(vel);
}

void Chell::mover_con_evento(EstadoTeclado& t){
	b2Vec2 vel = cuerpo->GetLinearVelocity();
	vel.x = CAMINAR * t.presionada(SDLK_RIGHT) + -CAMINAR * t.presionada(SDLK_LEFT);
	if (vel.y == 0)
		vel.y = SALTAR * t.presionada(SDLK_UP);
	cuerpo->SetLinearVelocity(vel);
}

b2Vec2 Chell::getPosition(){
	return cuerpo->GetPosition();
}