
#ifndef PANTALLA_ELEGIR_MAPA_H
#define PANTALLA_ELEGIR_MAPA_H

#include <string>
#include "skt.h"

class PantallaElegirMapa {
    Skt& skt;

public:
    PantallaElegirMapa(std::string puerto,
                          std::string host,
                          std::string& puerto_partida);

    // Devuelve si se debe continuar con el programa o no
    bool operator()();
};


#endif
