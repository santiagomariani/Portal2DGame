#include <iostream>
#include "chell.h"
#include "Box2D/Box2D.h"
#define TAMANIO_CHELL_X 0.25
#define TAMANIO_CHELL_Y 0.625
#define CAMINAR 0.5
#define SALTAR 6


Chell& Chell::operator=(Chell&& otro){
	if (this == &otro){
        return *this;
    }
    cuerpo = otro.cuerpo;
    otro.cuerpo = nullptr;
    cuerpo->SetUserData(this);
    return *this;
}
Chell::Chell(){
	cuerpo = nullptr;
}
Chell::Chell(Mundo& mundo, b2Vec2& pos){
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_dynamicBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo_def.fixedRotation = true;
	cuerpo = mundo.agregarBody(cuerpo_def);
	//cuerpo = world.CreateBody(&cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 4;
	myFixtureDef.friction = 0;
	myFixtureDef.restitution = 0;

	b2Vec2 pos_poligono(0, 0); // posicion del centro del poligono
	polygonShape.SetAsBox(TAMANIO_CHELL_X, TAMANIO_CHELL_Y, pos_poligono, 0);
	cuerpo->CreateFixture(&myFixtureDef);

	b2CircleShape circulo;
	b2FixtureDef circulo_fix_def;
	circulo_fix_def.shape = &circulo;
	circulo_fix_def.density = 1;
	circulo_fix_def.friction = 0;
	circulo_fix_def.restitution = 0;

	circulo.m_p.Set(0, -0.625); // posicion del centro del circulo
    circulo.m_radius = 0.25f;
	cuerpo->CreateFixture(&circulo_fix_def);
	cuerpo->SetUserData(this);

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
void Chell::mover(EstadoTeclado& t){
	b2Vec2 vel = cuerpo->GetLinearVelocity();
	vel.x = CAMINAR * t.presionada(SDLK_RIGHT) + -CAMINAR * t.presionada(SDLK_LEFT);
	if (vel.y == 0)
		vel.y = SALTAR * t.presionada(SDLK_UP);
	cuerpo->SetLinearVelocity(vel);
}
int Chell::getId(){
	return 0;
}
const b2Vec2& Chell::getPosition(){
	return cuerpo->GetPosition();
}
Chell::Chell(Chell&& otro){
    if (this == &otro){
        return;
    }
    cuerpo = otro.cuerpo;
    cuerpo->SetUserData(this);
    otro.cuerpo = nullptr;
}
void Chell::disparar(Mundo& mundo, b2Vec2& pos_click){
	b2Vec2 pos_inicial(0,0.53f);
	pos_inicial += this->getPosition();
	this->disparo.activar(mundo, pos_inicial, pos_click);
}
float Chell::getWidth(){
	return TAMANIO_CHELL_X * 2;
}
float Chell::getHeight(){
	return TAMANIO_CHELL_Y * 2 + 0.25;
}
