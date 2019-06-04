//
// Created by santi on 04/06/19.
//

#include "Acido.h"
#include "ids.h"
#include "chell.h"

Acido::Acido(Mundo &mundo, b2Vec2 &pos) : Cuerpo(TAMANIO_ACIDO_X * 2, TAMANIO_ACIDO_Y * 2){
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(body_def);
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.isSensor = true;
    fixture_def.shape = &polygon_shape;
    polygon_shape.SetAsBox(TAMANIO_ACIDO_X, TAMANIO_ACIDO_Y);
    cuerpo->CreateFixture(&fixture_def);
    cuerpo->SetUserData(this);
}

const b2Vec2 &Acido::getPosition() {
    return cuerpo->GetPosition();
}

int Acido::getId() {
    return ID_ACIDO;
}

b2Body *Acido::getBody() {
    return cuerpo;
}

void Acido::empezarContacto(Cuerpo *otro) {
    if (otro->getId() == ID_CHELL) {
        ((Chell*)otro)->morir();
    }
}

void Acido::terminarContacto(Cuerpo *otro) {

}
