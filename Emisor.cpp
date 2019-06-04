//
// Created by santi on 01/06/19.
//

#include "Emisor.h"
#include <iostream>
#include "ids.h"

Emisor::Emisor(Mundo &mundo, const b2Vec2 &pos) :
        mundo(mundo),
        Cuerpo(TAMANIO_EMISOR * 2, TAMANIO_EMISOR * 2){
    contador = 0;
    mundo.agregarCuerpoAActualizar(this);
    b2BodyDef cuerpo_def;
    cuerpo_def.type = b2_staticBody;
    cuerpo_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(cuerpo_def);
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    polygon_shape.SetAsBox(TAMANIO_EMISOR, TAMANIO_EMISOR);
    cuerpo->CreateFixture(&fixture_def);
    cuerpo->SetUserData(this);
}

Emisor::Emisor(Mundo &mundo) : mundo(mundo) {
}

const b2Vec2 &Emisor::getPosition() {
    return cuerpo->GetPosition();
}

void Emisor::empezarContacto(Cuerpo *otro) {

}

void Emisor::terminarContacto(Cuerpo *otro) {

}

b2Body *Emisor::getBody() {
    return cuerpo;
}

void Emisor::emitirBolaEnergia() {
    // Veo si finalizo alguna bola de energia.

    for (auto it = bolas_energia.begin();it != bolas_energia.end();) {
        if ((*it)->bolaFinalizo()) {
            it = bolas_energia.erase(it);
        }
        else {
            ++it;
        }
    }

    bolas_energia.emplace_back(new BolaEnergia(mundo, pos_creacion, dir_vel));
}

void Emisor::actualizar() {
    contador++;
    if (contador == FRECUENCIA) {
        this->emitirBolaEnergia();
        contador = 0;
    }
}
