#ifndef SELECTOR_PARTIDA_H
#define SELECTOR_PARTIDA_H

#include <string>
#include "protocolo.h"
#include "ventana.h"

class SelectorPartida{
    Protocolo& protocolo;

public:
    SelectorPartida(Protocolo& protocolo);

    // Devuelve si se debe continuar con el programa o no
    bool operator()(Ventana& ventana, std::string& puerto);
};


#endif //SELECTOR_PARTIDA_H
