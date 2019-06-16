
#include <iostream>
#include <config.h>
#include "BarraDeEnergia.h"
#include "ids.h"
#include "chell.h"

BarraDeEnergia::BarraDeEnergia(Mundo &mundo, b2Vec2 &pos) :
    Cuerpo(config.tam_barra_energia_x * 2,
           config.tam_barra_energia_y * 2) {
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(body_def);
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.isSensor = true;
    fixture_def.shape = &polygon_shape;
    polygon_shape.SetAsBox(config.tam_barra_energia_x,
                           config.tam_barra_energia_y);
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
