
#ifndef PANTALLA_ELEGIR_MAPA_H
#define PANTALLA_ELEGIR_MAPA_H

#include <string>
#include "protocolo.h"
#include "ventana.h"

class PantallaElegirMapa{
    Protocolo& protocolo;

public:
    PantallaElegirMapa(Protocolo& protocolo);

    // Devuelve si se debe continuar con el programa o no
    bool operator()(Ventana& ventana);
};


#endif
