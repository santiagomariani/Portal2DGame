//
// Created by santi on 14/06/19.
//

#include "SonidosChell.h"
#include "EstadoChell.h"
#define CHELL_DISPARA 254

SonidosChell::SonidosChell() {
    creacionSonidos();
}

void SonidosChell::creacionSonidos() {
    // Chell dispara.
    std::string chell_dispara = "assets/sonidos/chell_dispara.wav";
    sonidos.insert(std::make_pair(CHELL_DISPARA, Sonido(chell_dispara, 1)));
    sonidos.at(CHELL_DISPARA).setearVolumen(100);

    // Chell salta.
    std::string chell_salta = "assets/sonidos/chell_salta.wav";
    sonidos.insert(std::make_pair(CHELL_SALTA, Sonido(chell_salta, 2)));

    // Chell muere.
    std::string chell_muere = "assets/sonidos/chell_muere.wav";
    sonidos.insert(std::make_pair(CHELL_MUERE, Sonido(chell_muere, 3)));
    sonidos.at(CHELL_MUERE).setearVolumen(40);
}

void SonidosChell::reproducir(uint8_t estado) {
    if (dispara(estado)) {
        sonidos.at(CHELL_DISPARA).reproducirUnaVez();
    } else if (sonidos.count(estado)) {
        sonidos.at(estado).reproducirUnaVez();
    }
}

bool SonidosChell::dispara(uint8_t estado) {
    return (estado == CHELL_MOVIENDOSE_Y_DISPARA)
        || (estado == CHELL_EN_EL_AIRE_Y_DISPARA)
        || (estado == CHELL_QUIETA_Y_DISPARA);
}
