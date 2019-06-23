#ifndef PANTALLA_ESPERANDO_H
#define PANTALLA_ESPERANDO_H

#include <string>
#include "protocolo.h"
#include "ventana.h"

class PantallaEsperando{

public:
    PantallaEsperando();

    // Devuelve el id asignado al cliente
    int operator()(Protocolo& protocolo, Skt& skt);
};


#endif //PANTALLA_ESPERANDO_H
