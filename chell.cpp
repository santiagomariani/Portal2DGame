#include <iostream>
#include "chell.h"
#include "pistola.h"
#include "Box2D/Box2D.h"
#include "ids.h"

#define TAMANIO_CHELL_X 0.40f
#define TAMANIO_CHELL_Y 0.625f
#define RADIO 0.25f
#define CAMINAR 4
#define SALTAR 5

Chell::Chell(int identidad, Mundo& mundo) :
        Cuerpo(TAMANIO_CHELL_X*2, TAMANIO_CHELL_Y*2 + RADIO),
        id(identidad),
        mundo(mundo),
        pistola(mundo),
        roca(nullptr),
        joint_roca(nullptr) {
	cuerpo = nullptr;
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
    myFixtureDef.density = 7;
    myFixtureDef.friction = 0;
    //myFixtureDef.restitution = 0;

    b2Vec2 pos_poligono(0, 0.125f); // posicion del centro del poligono
    polygonShape.SetAsBox(TAMANIO_CHELL_X, TAMANIO_CHELL_Y, pos_poligono, 0);
    cuerpo->CreateFixture(&myFixtureDef);

    b2CircleShape circulo;
    b2FixtureDef circulo_fix_def;
    circulo_fix_def.shape = &circulo;
    circulo_fix_def.density = 7;
    circulo_fix_def.friction = 0;
    //circulo_fix_def.restitution = 0;

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
        mundo(otro.mundo),
        pistola(std::move(otro.pistola)) {
    if (this == &otro){
        return;
    }
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;
    cuerpo = otro.cuerpo;
    roca = otro.roca;
    joint_roca = otro.joint_roca;

    id = otro.id;
    otro.maxWidth = 0;
    otro.maxHeight = 0;
    otro.cuerpo = nullptr;
    otro.roca = nullptr;
    otro.joint_roca = nullptr;
	if (cuerpo){
		cuerpo->SetUserData(this);
	}
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

b2Body* Chell::getBody(){
	return cuerpo;
}

void Chell::agarrarRoca(EstadoTeclado &t) {
    if ((t.presionada(SDLK_e)) && (roca != nullptr)) {
        std::cout << "e" << std::endl;
        if (joint_roca == nullptr) {
            b2Vec2 nueva_pos_roca(
                    this->getPosition().x + TAMANIO_CHELL_X + (roca->getMaxWidth() / 2),
                    this->getPosition().y);
            roca->getBody()->SetTransform(nueva_pos_roca, 0);
            std::cout << "se crea joint" << std::endl;
            b2DistanceJointDef joint_def;
            joint_def.Initialize(this->getBody(),
                                 roca->getBody(),
                                 this->getPosition(),
                                 roca->getPosition());
            joint_def.collideConnected = true;
            joint_def.frequencyHz = 4.0f;
            joint_def.dampingRatio = 0.5f;
            joint_roca = (getBody()->GetWorld())->CreateJoint(&joint_def);
        } else {
            std::cout << "se elimina joint" << std::endl;
            getBody()->GetWorld()->DestroyJoint(joint_roca);
            joint_roca = nullptr;
        }
    }
}

void Chell::empezarContacto(Cuerpo* otro){
    if (otro->getId() == ID_ROCA) {
        roca = (Roca*)otro;
        std::cout << "empezo contacto con roca" << std::endl;
    }
}

void Chell::terminarContacto(Cuerpo *otro) {
    if (otro->getId() == ID_ROCA && !joint_roca) {
        roca = nullptr;
        std::cout << "termino contacto con roca" << std::endl;
    }
}

