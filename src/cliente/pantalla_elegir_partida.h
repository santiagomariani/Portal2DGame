
#ifndef PANTALLA_ELEGIR_PARTIDA_H
#define PANTALLA_ELEGIR_PARTIDA_H


#include <string>
#include <Skt.h>

class PantallaElegirPartida {
    std::string& puerto;
    Skt skt;

public:
    PantallaElegirPartida(std::string puerto,
                          std::string host,
                          std::string& puerto_partida);

    // Devuelve si se debe continuar con el programa o no
    bool operator()();
};


#endif
