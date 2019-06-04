//
// Created by santi on 02/06/19.
//

#include <iostream>
#include "Receptor.h"

Receptor::Receptor(Mundo &mundo, const b2Vec2 &pos) :
    Cuerpo(TAMANIO_RECEPTOR * 2, TAMANIO_RECEPTOR * 2),
    activado(false),
    sensor(new SensorReceptor(*this)) {
    b2BodyDef receptor_def;
    receptor_def.type = b2_staticBody;
    receptor_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(receptor_def);
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    polygon_shape.SetAsBox(TAMANIO_RECEPTOR, TAMANIO_RECEPTOR);
    cuerpo->CreateFixture(&fixture_def);
    cuerpo->SetUserData(this);
}

const b2Vec2 &Receptor::getPosition() {
    return cuerpo->GetPosition();
}

b2Body *Receptor::getBody() {
    return cuerpo;
}

void Receptor::activar() {
    activado = true;
    std::cout << "se activa receptor" << std::endl;
}

bool Receptor::estaActivado() {
    return activado;
}

void Receptor::empezarContacto(Cuerpo *otro) {
}

void Receptor::terminarContacto(Cuerpo *otro) {
}
