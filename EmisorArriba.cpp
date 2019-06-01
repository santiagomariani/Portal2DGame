//
// Created by santi on 31/05/19.
//

#include <iostream>
#include "EmisorArriba.h"
#include "ids.h"

EmisorArriba::EmisorArriba(Mundo &mundo, const b2Vec2 &pos) :
    mundo(mundo),
    Cuerpo(TAMANIO_EMISOR * 2, TAMANIO_EMISOR * 2){
    contador = 0;
    std::cout << "HOLA4" << std::endl;
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

EmisorArriba::EmisorArriba(EmisorArriba &&otro) :
    mundo(otro.mundo),
    Cuerpo(otro.maxWidth, otro.maxHeight) {
    if (this == &otro) {
        return;
    }
    std::cout << "HOLA3" << std::endl;
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;
    cuerpo = otro.cuerpo;
    contador = otro.contador;

    otro.maxWidth = 0;
    otro.maxHeight = 0;
    otro.cuerpo = nullptr;
    otro.contador = 0;

    cuerpo->SetUserData(this);
}

EmisorArriba &EmisorArriba::operator=(EmisorArriba &otro) {
    if (this == &otro) {
        return *this;
    }
    std::cout << "HOLA2" << std::endl;
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;
    mundo = otro.mundo;
    cuerpo = otro.cuerpo;
    contador = otro.contador;
    cuerpo->SetUserData(this);
    return *this;
}

EmisorArriba &EmisorArriba::operator=(EmisorArriba &&otro) {
    if (this == &otro) {
        return *this;
    }
    std::cout << "HOLA1" << std::endl;
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;
    mundo = otro.mundo;
    cuerpo = otro.cuerpo;
    contador = otro.contador;

    otro.maxWidth = 0;
    otro.maxHeight = 0;
    otro.cuerpo = nullptr;
    otro.contador = 0;
    cuerpo->SetUserData(this);
    return *this;
}

int EmisorArriba::getId() {
    return ID_EMISORARRIBA;
}

const b2Vec2 &EmisorArriba::getPosition() {
    return cuerpo->GetPosition();
}

void EmisorArriba::empezarContacto(Cuerpo *otro) {

}

void EmisorArriba::terminarContacto(Cuerpo *otro) {

}

b2Body *EmisorArriba::getBody() {
    return cuerpo;
}

void EmisorArriba::emitirBolaEnergia() {

    // Veo si finalizo alguna bola de energia.
    for (auto it = bolas_energia.begin();it != bolas_energia.end();) {
        if ((*it).bolaFinalizo()) {
            it = bolas_energia.erase(it);
        }
        else {
            ++it;
        }
        std::cout << "COMPRUEBA BOLAS" << std::endl;
    }
    const b2Vec2 &posEmisor = this->getPosition();
    b2Vec2 pos(posEmisor.x, posEmisor.y + (maxHeight / 2) + RADIO_BOLAENERGIA);
    b2Vec2 dir(0, 1);
    bolas_energia.emplace_back(mundo, pos, dir);
}

void EmisorArriba::actualizar() {
    // std::cout << "ACTUALIZA EMISOR" << std::endl;
    contador++;
    if (contador == FRECUENCIA) {
        std::cout << "EMITE BOLA ENERGIA" << std::endl;
        this->emitirBolaEnergia();
        contador = 0;
    }
}
