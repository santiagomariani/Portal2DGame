//
// Created by santi on 06/06/19.
//

#include <iostream>
#include "SensorChell.h"
#include "ids.h"

SensorChell::SensorChell() : activado(false),
cant_contactos(0) {
}

bool SensorChell::estaActivado() {
    return activado;
}

void SensorChell::empezarContacto(Cuerpo *otro) {
    if (otro->getId() == ID_DISPARO || otro->getId() == ID_ACIDO
    || otro->getId() == ID_BOLAENERGIA || otro->getId() == ID_BARRAENERGIA
    || otro->getId() == ID_CHELL) {
        return;
    }
    cant_contactos++;
    if (cant_contactos == 0) {
        activado = false;
    } else {
        activado = true;
    }
}

void SensorChell::terminarContacto(Cuerpo *otro) {
    if (otro->getId() == ID_DISPARO || otro->getId() == ID_ACIDO
        || otro->getId() == ID_BOLAENERGIA || otro->getId() == ID_BARRAENERGIA
        || otro->getId() == ID_CHELL) {
        return;
    }
    cant_contactos--;
    if (cant_contactos == 0) {
        activado = false;
    } else {
        activado = true;
    }
}
