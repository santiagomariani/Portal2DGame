
#include "bloque_metal_diagonal.h"
#include "angulo_cero.h"
#include "ids.h"
#include <iostream>
#include "cuerpo.h"
#include <cmath>
#include "config.h"

#define PI 3.14159265


BloqueMetalDiagonal::BloqueMetalDiagonal(Mundo &mundo, const b2Vec2 &pos, Angulo& angulo) :
    Bloque(config.tam_bloque * 2, config.tam_bloque * 2), angulo(angulo) {

    b2BodyDef cuerpo_def;
    cuerpo_def.type = b2_staticBody;
    cuerpo_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(cuerpo_def);

    b2PolygonShape polygonShape = angulo.obtenerTriangulo();
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;

    cuerpo->CreateFixture(&myFixtureDef);
    cuerpo->SetUserData(this);

    this->crearMapaIds();
}

BloqueMetalDiagonal::BloqueMetalDiagonal(BloqueMetalDiagonal&& otro) :
            Bloque(config.tam_bloque * 2, config.tam_bloque * 2),
            angulo(otro.angulo){
    if (this == &otro){
        return;
    }
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;
    mapa_ids = otro.mapa_ids;

    otro.maxWidth = 0;
    otro.maxHeight = 0;
    cuerpo = otro.cuerpo;
    cuerpo->SetUserData(this);
    otro.cuerpo = nullptr;
}

const b2Vec2& BloqueMetalDiagonal::getPosition(){
    return cuerpo->GetPosition();
}

void BloqueMetalDiagonal::crearMapaIds(){
    mapa_ids[0] = ID_BLOQUE_DIAGONAL_0;
    mapa_ids[90] = ID_BLOQUE_DIAGONAL_90;
    mapa_ids[180] = ID_BLOQUE_DIAGONAL_180;
    mapa_ids[270] = ID_BLOQUE_DIAGONAL_270;
}

uint8_t BloqueMetalDiagonal::getId(){
    //return mapa_ids[angulo];
    return this->angulo.getId();
}

void BloqueMetalDiagonal::recibirDisparo(Disparo* disparo) {
    b2Vec2 bloque = this->getPosition();
    b2Vec2 pos = disparo->getPosition();
    pos -= bloque;

    b2Vec2 pos_portal = this->angulo.obtenerPosPortal(pos);
    b2Vec2 normal_portal = this->angulo.obtenerNormalPortal(pos);
    pos_portal += bloque;
    //std::cout << pos_portal.x << " " << pos_portal.y << std::endl;

    disparo->crearPortal(pos_portal, normal_portal);
}

void BloqueMetalDiagonal::empezarContacto(Cuerpo* otro){
    if (otro->getId() == ID_DISPARO){
        this->recibirDisparo((Disparo*)otro);
        ((Disparo*)otro)->terminar();
    }
}
