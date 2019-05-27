#include <iostream>
#include "chell.h"
#include "pistola.h"
#include "Box2D/Box2D.h"
#define TAMANIO_CHELL_X 0.4f
#define TAMANIO_CHELL_Y 0.625f
#define RADIO 0.25f
#define CAMINAR 3
#define SALTAR 5

Chell::Chell(int identidad, Mundo& mundo) : 
        Cuerpo(TAMANIO_CHELL_X*2, TAMANIO_CHELL_Y*2 + RADIO),
        id(identidad), mundo(mundo), pistola(mundo){
    cuerpo = nullptr;
}

Chell& Chell::operator=(Chell&& otro){
    if (this == &otro){
        return *this;
    }
    pistola = std::move(otro.pistola);
    mundo = std::move(otro.mundo);
    id = otro.id;
    cuerpo = otro.cuerpo;
    otro.cuerpo = nullptr;
    cuerpo->SetUserData(this);
    return *this;
}
void Chell::activar(b2Vec2& pos){
    if (cuerpo){
        mundo.destruirBody(cuerpo);
        cuerpo = nullptr;
    }
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

    b2Vec2 pos_poligono(0, 0.125f); // posicion del centro del poligono
    polygonShape.SetAsBox(TAMANIO_CHELL_X, TAMANIO_CHELL_Y, pos_poligono, 0);
    cuerpo->CreateFixture(&myFixtureDef);

    b2CircleShape circulo;
    b2FixtureDef circulo_fix_def;
    circulo_fix_def.shape = &circulo;
    circulo_fix_def.density = 1;
    circulo_fix_def.friction = 0;
    circulo_fix_def.restitution = 0;

    circulo.m_p.Set(0, -2*RADIO); // posicion del centro del circulo
    circulo.m_radius = RADIO;
    cuerpo->CreateFixture(&circulo_fix_def);
    cuerpo->SetUserData(this);
}
int Chell::getId(){
    return id;
}

Chell::Chell(Chell&& otro) :
        Cuerpo(TAMANIO_CHELL_X*2, TAMANIO_CHELL_Y*2 + RADIO),
        mundo(otro.mundo), pistola(std::move(otro.pistola)) {
    if (this == &otro){
        return;
    }
    std::cout << "moviendo " << id << std::endl;
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;
    cuerpo = otro.cuerpo;

    id = otro.id;
    otro.maxWidth = 0;
    otro.maxHeight = 0;
    otro.cuerpo = nullptr;
    cuerpo->SetUserData(this);
}


void Chell::mover(EstadoTeclado& t){
    b2Vec2 vel = cuerpo->GetLinearVelocity();
    vel.x = CAMINAR * t.presionada(SDLK_RIGHT) + -CAMINAR * t.presionada(SDLK_LEFT);
    if (vel.y == 0)
        vel.y = SALTAR * t.presionada(SDLK_UP);
    cuerpo->SetLinearVelocity(vel);
}

const b2Vec2& Chell::getPosition(){
    return cuerpo->GetPosition();
}
const b2Vec2& Chell::getVelocidad(){
    return cuerpo->GetLinearVelocity();
}
void Chell::setVelocidad(b2Vec2& vel){
    cuerpo->SetLinearVelocity(vel);
}
void Chell::cambiarPosicion(const b2Vec2& pos){
    cuerpo->SetTransform(pos, 0.0f);
}

void Chell::dispararAzul(b2Vec2& pos_click){
    pistola.dispararAzul(getPosition(), pos_click);
}

void Chell::dispararNaranja(b2Vec2& pos_click){
    pistola.dispararNaranja(getPosition(), pos_click);
}

float Chell::getWidth(){
    return float(TAMANIO_CHELL_X * 2);
}
float Chell::getHeight(){
    return float(TAMANIO_CHELL_Y * 2 + 0.25);
}
