
#include <iostream>
#include <config.h>
#include "emisor_abajo.h"
#include "ids.h"

EmisorAbajo::EmisorAbajo(Mundo &mundo, const b2Vec2 &pos) :
        Emisor(mundo, pos) {
    pos_creacion = b2Vec2(pos.x,
            pos.y-(maxHeight/2)-config.radio_bola_energia-0.1);
    dir_vel = b2Vec2(0, -1);
}

EmisorAbajo::EmisorAbajo(EmisorAbajo &&otro) : Emisor(otro.mundo) {
    if (this == &otro) {
        return;
    }
    bolas_energia = std::move(otro.bolas_energia);
    pos_creacion = otro.pos_creacion;
    dir_vel = otro.dir_vel;
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

EmisorAbajo &EmisorAbajo::operator=(EmisorAbajo &&otro) {
    if (this == &otro) {
        return *this;
    }
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;
    cuerpo = otro.cuerpo;
    contador = otro.contador;
    bolas_energia = std::move(otro.bolas_energia);
    pos_creacion = otro.pos_creacion;
    dir_vel = otro.dir_vel;

    otro.maxWidth = 0;
    otro.maxHeight = 0;
    otro.cuerpo = nullptr;
    otro.contador = 0;

    cuerpo->SetUserData(this);
    return *this;
}

uint8_t EmisorAbajo::getId() {
    return ID_EMISORABAJO;
}
