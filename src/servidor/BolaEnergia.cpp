//
// Created by santi on 31/05/19.
//

#include "BolaEnergia.h"
#include "ids.h"
#include "chell.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265

BolaEnergia::BolaEnergia(Mundo &mundo, b2Vec2 &pos, b2Vec2 &dir_vel) :
    Cuerpo(RADIO_BOLAENERGIA * 2, RADIO_BOLAENERGIA * 2),
    mundo(mundo){
    contador = 0;
    finalizo = false;
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set(pos.x, pos.y);
    body_def.fixedRotation = true;
    body_def.bullet = true;
    cuerpo = mundo.agregarBody(body_def);
    b2CircleShape circle_shape;
    circle_shape.m_p.Set(0, 0);
    circle_shape.m_radius = RADIO_BOLAENERGIA;
    b2FixtureDef fixture_def;
    fixture_def.shape = &circle_shape;
    fixture_def.density = DENSIDAD_BOLAENERGIA;
    cuerpo->CreateFixture(&fixture_def);
    b2Vec2 vel = dir_vel;
    vel.Normalize();
    vel *= CTE_VELOCIDAD_BOLAENERGIA;
    cuerpo->SetGravityScale(0);
    cuerpo->SetLinearVelocity(vel);
    cuerpo->SetUserData(this);
    mundo.agregarCuerpoAActualizar(this);
    //ya_choque = false;
}

void BolaEnergia::actualizar() {
    contador++;
    if ((contador == TIEMPO_VIDA) && cuerpo) {
        finalizo = true;
        mundo.destruirBody(this->cuerpo);
    }
}

BolaEnergia::BolaEnergia(BolaEnergia &&otro) :
    Cuerpo(otro.maxWidth, otro.maxHeight),
    mundo(otro.mundo){
    if (this == &otro) {
        return;
    }
    cuerpo = otro.cuerpo;
    contador = otro.contador;
    finalizo = otro.finalizo;

    otro.maxWidth = 0;
    otro.maxHeight = 0;
    otro.cuerpo = nullptr;
    otro.contador = 0;
    otro.finalizo = false;
    if (cuerpo) {
        cuerpo->SetUserData(this);
    }
}

BolaEnergia &BolaEnergia::operator=(BolaEnergia &&otro) {
    if (this == &otro) {
        return *this;
    }
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;
    mundo = otro.mundo;
    cuerpo = otro.cuerpo;
    contador = otro.contador;
    finalizo = otro.finalizo;

    otro.maxWidth = 0;
    otro.maxHeight = 0;
    otro.cuerpo = nullptr;
    otro.contador = 0;
    otro.finalizo = false;
    cuerpo->SetUserData(this);
    return *this;
}

bool BolaEnergia::bolaFinalizo() {
    return finalizo;
}

const b2Vec2 &BolaEnergia::getPosition() {
    return cuerpo->GetPosition();
}

int32_t BolaEnergia::getAngle() {
    b2Vec2 vel = cuerpo->GetLinearVelocity();
    float angulo = atan2(vel.y, vel.x);
    return (uint32_t)(angulo * 180/PI);
}

uint8_t BolaEnergia::getId() {
    return ID_BOLAENERGIA;
}

void BolaEnergia::desactivar(){
    if (this->cuerpo){
        mundo.destruirBody(this->cuerpo);
        this->cuerpo = nullptr;
    }
}

void BolaEnergia::empezarContacto(Cuerpo *otro) {
    /*
    if (ya_choque) {
        return;
    }
    */
    if (otro->getId() == ID_CHELL) {
        //ya_choque = true;
        ((Chell*)otro)->morir();
    } else if (otro->getId() == ID_BLOQUE_METAL ||
    otro->getId() == ID_BLOQUE_DIAGONAL_0 ||
    otro->getId() == ID_BLOQUE_DIAGONAL_90 ||
    otro->getId() == ID_BLOQUE_DIAGONAL_180 ||
    otro->getId() == ID_BLOQUE_DIAGONAL_270) {
        return;
    }
    mundo.agregarCuerpoADestruir(this);
}

void BolaEnergia::terminarContacto(Cuerpo *otro) {
}

b2Body *BolaEnergia::getBody() {
    return cuerpo;
}

void BolaEnergia::agregarCuerpoADestruir() {
    mundo.agregarCuerpoADestruir(this);
}
