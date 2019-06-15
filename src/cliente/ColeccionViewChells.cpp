//
// Created by santi on 14/06/19.
//

#include "ColeccionViewChells.h"

ColeccionViewChells::ColeccionViewChells(Ventana &ventana) {
    std::string chell_verde = "assets/chell_verde.png";
    view_chells.emplace_back(ventana, chell_verde);
    std::string chell_roja = "assets/chell_roja.png";
    view_chells.emplace_back(ventana, chell_roja);
    std::string chell_violeta = "assets/chell_violeta.png";
    view_chells.emplace_back(ventana, chell_violeta);
    std::string chell_azul = "assets/chell_azul.png";
    view_chells.emplace_back(ventana, chell_azul);
}

ViewChell &ColeccionViewChells::obtenerViewChell(uint8_t id_jugador) {
    return view_chells[id_jugador];
}
