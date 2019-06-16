
#ifndef BOTON_NUEVA_PARTIDA_H
#define BOTON_NUEVA_PARTIDA_H


#include <Protocolo.h>
#include "presionable.h"

class BotonNuevaPartida : public Presionable{
    bool* corriendo;
    Protocolo& protocolo;
    std::string& puerto;
public:
    BotonNuevaPartida(Imagen* imagen,
                        bool* corriendo,
                        Protocolo& protocolo,
                        std::string& puerto);

    void presionar() override;
};



#endif

