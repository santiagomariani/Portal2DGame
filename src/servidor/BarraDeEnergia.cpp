//
// Created by santi on 04/06/19.
//

#include <iostream>
#include "BarraDeEnergia.h"
#include "ids.h"
#include "chell.h"

BarraDeEnergia::BarraDeEnergia(Mundo &mundo, b2Vec2 &pos) :
    Cuerpo(TAMANIO_BARRAENERGIA_X * 2,
            TAMANIO_BARRAENERGIA_Y * 2) {
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(body_def);
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.isSensor = true;
    fixture_def.shape = &polygon_shape;
    polygon_shape.SetAsBox(TAMANIO_BARRAENERGIA_X, TAMANIO_BARRAENERGIA_Y);
    cuerpo->CreateFixture(&fixture_def);
    cuerpo->SetUserData(this);
}

const b2Vec2 &BarraDeEnergia::getPosition() {
    return cuerpo->GetPosition();
}

uint8_t BarraDeEnergia::getId() {
    return ID_BARRAENERGIA;
}

b2Body *BarraDeEnergia::getBody() {
    return cuerpo;
}

void BarraDeEnergia::empezarContacto(Cuerpo *cuerpo) {
    if (cuerpo->getId() == ID_CHELL) {
        ((Chell*)cuerpo)->destruirRoca();
    }
}

void BarraDeEnergia::terminarContacto(Cuerpo *cuerpo) {

}
