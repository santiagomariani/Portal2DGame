
#ifndef PANTALLA_ELEGIR_MAPA_H
#define PANTALLA_ELEGIR_MAPA_H

#include <string>
#include "skt.h"
#include "ventana.h"

class PantallaElegirMapa{
    Skt& skt;

public:
    PantallaElegirMapa(Skt& skt);

    // Devuelve si se debe continuar con el programa o no
    bool operator()(Ventana& ventana);
};


#endif
