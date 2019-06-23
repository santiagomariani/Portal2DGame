
#include <path.h>
#include "coleccion_vista_chells.h"

ColeccionVistaChells::ColeccionVistaChells(Ventana &ventana) {
    std::string assets_path = ASSETS;

    std::string chell_verde = assets_path + "assets/chell_verde.png";
    vista_chells.emplace_back(ventana, chell_verde);
    std::string chell_roja = assets_path + "assets/chell_roja.png";
    vista_chells.emplace_back(ventana, chell_roja);
    std::string chell_violeta = assets_path + "assets/chell_violeta.png";
    vista_chells.emplace_back(ventana, chell_violeta);
    std::string chell_azul = assets_path + "assets/chell_azul.png";
    vista_chells.emplace_back(ventana, chell_azul);
}

VistaChell &ColeccionVistaChells::obtenerVistaChell(uint8_t id_jugador) {
    return vista_chells[id_jugador];
}
