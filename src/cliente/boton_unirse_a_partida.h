
#ifndef BOTON_UNIRSE_A_PARTIDA_H
#define BOTON_UNIRSE_A_PARTIDA_H

#include "protocolo.h"
#include "presionable.h"

class BotonUnirseAPartida : public Presionable{
    bool* corriendo;
    Protocolo& protocolo;
    std::string& puerto;
public:
    BotonUnirseAPartida(Imagen* imagen,
                      bool* corriendo,
                      Protocolo& protocolo,
                      std::string& puerto);

    void presionar() override;
};



#endif

