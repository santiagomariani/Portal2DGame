//
// Created by santi on 31/05/19.
//

#include <iostream>
#include "EmisorDerecha.h"
#include "ids.h"

EmisorDerecha::EmisorDerecha(Mundo &mundo, const b2Vec2 &pos) :
        Emisor(mundo, pos) {
    pos_creacion = b2Vec2(pos.x + (maxWidth / 2) + RADIO_BOLAENERGIA + 0.1, pos.y);
    dir_vel = b2Vec2(1, 0);
}

EmisorDerecha::EmisorDerecha(EmisorDerecha &&otro) : Emisor(otro.mundo) {
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

EmisorDerecha &EmisorDerecha::operator=(EmisorDerecha &&otro) {
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

int EmisorDerecha::getId() {
    return ID_EMISORDERECHA;
}
