#include "portal.h"
#include "chell.h"
#include "ids.h"
#include "teletransportador.h"
#include <math.h>
#include "Box2D/Box2D.h"
#include "config.h"

#define PI 3.14159265

Portal::Portal(int identidad, Mundo& mundo) : 
        Cuerpo(config.tam_portal_x*2, config.tam_portal_y*2),
        id(identidad), mundo(mundo), pos(0, 0), normal(0, 0){
    orientacion = 0.0f;
    hermano = nullptr;
    cuerpo = nullptr;
    orientacion = 0.0f;
}

void Portal::activar(){
    if (cuerpo){
        mundo.destruirBody(cuerpo);
        cuerpo = nullptr;
    }
    orientacion = atan2(normal.y, normal.x);
    if (orientacion < 0){
        orientacion += 2 * PI;
    }

    b2BodyDef cuerpo_def;
    cuerpo_def.type = b2_staticBody;
    cuerpo_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(cuerpo_def);

    b2PolygonShape polygonShape;
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;

    b2Vec2 centro(0,0);
    polygonShape.SetAsBox(config.tam_portal_x, config.tam_portal_y, centro, orientacion);
    cuerpo->CreateFixture(&myFixtureDef);
    cuerpo->SetUserData(this);
}

void Portal::conectar(Portal* otro){
    hermano = otro;
}

float Portal::getAnguloSalida(){
    return orientacion;
}

uint8_t Portal::getId(){
    return id;
}

const b2Vec2& Portal::getPosition(){
    return cuerpo->GetPosition();
}

float Portal::getAnguloEntrada(){
    if (orientacion - PI < 0){
        return orientacion + PI;
    }
    return orientacion - PI;
}

void Portal::expulsar(b2Body* objeto, float orientacion_otro){
    if (!cuerpo)
        return;
    float nuevo_ang = getAnguloSalida() - orientacion_otro;
    b2Rot rotador(nuevo_ang);
    b2Vec2 vel = objeto->GetLinearVelocity();
    b2Vec2 nueva_vel = b2Mul(rotador, vel);
    nueva_vel *= 1;

    b2Vec2 nueva_pos = (cuerpo->GetPosition() + (0.7f * normal));

    mundo.agregarTransportador(objeto, nueva_pos, nueva_vel);
}

void Portal::teletransportar(b2Body* objeto){
    if (!cuerpo)
        return;
    hermano->expulsar(objeto, getAnguloEntrada());
}

void Portal::establecer(b2Vec2& posicion, b2Vec2& normal_entrada) {
    pos.x = posicion.x;
    pos.y = posicion.y;
    normal.x = normal_entrada.x;
    normal.y = normal_entrada.y;
}

Portal::Portal(Portal&& otro): 
        Cuerpo(config.tam_portal_y*2, config.tam_portal_y*2),
        mundo(otro.mundo){
    pos = otro.pos;
    normal = otro.normal;
    id = otro.id;
    hermano = otro.hermano;
    otro.hermano = nullptr;
    cuerpo = otro.cuerpo;
    otro.cuerpo = nullptr;
    orientacion = otro.orientacion;
    otro.orientacion = 0;
}

void Portal::empezarContacto(Cuerpo* otro){
	switch (otro->getId()){
		case(ID_CHELL):
		case(ID_ROCA):
		case(ID_BOLAENERGIA):
			teletransportar(otro->getBody());
	}
}

int32_t Portal::getAngle() {
    return (uint32_t)(orientacion * 180/PI);
}

