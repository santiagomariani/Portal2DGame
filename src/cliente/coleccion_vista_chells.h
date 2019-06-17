
#ifndef COLECCION_VISTA_CHELLS_H
#define COLECCION_VISTA_CHELLS_H


#include "vista_chell.h"

class ColeccionVistaChells {
private:
    std::vector<VistaChell> vista_chells;

public:
    // Crea las distintas Chells (distintos colores para cada jugador).
    ColeccionVistaChells(Ventana &ventana);
    // Devuelve la Chell asociada al jugador.
    VistaChell& obtenerVistaChell(uint8_t id_jugador);
};


#endif //COLECCION_VISTA_CHELLS_H
