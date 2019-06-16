
#include "Emisor.h"
#include <iostream>
#include <config.h>
#include "ids.h"

Emisor::Emisor(Mundo &mundo, const b2Vec2 &pos) :
        Cuerpo(config.tam_emisor * 2, config.tam_emisor * 2),
        mundo(mundo){
    contador = 0;
    mundo.agregarCuerpoAActualizar(this);
    b2BodyDef cuerpo_def;
    cuerpo_def.type = b2_staticBody;
    cuerpo_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(cuerpo_def);
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    polygon_shape.SetAsBox(config.tam_emisor, config.tam_emisor);
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
