//
// Created by santi on 14/06/19.
//

#ifndef COLECCIONVIEWCHELLS_H
#define COLECCIONVIEWCHELLS_H


#include "ViewChell.h"

class ColeccionViewChells {
private:
    std::vector<ViewChell> view_chells;
public:
    ColeccionViewChells(Ventana &ventana);
    ViewChell& obtenerViewChell(uint8_t id_jugador);
};


#endif //COLECCIONVIEWCHELLS_H
