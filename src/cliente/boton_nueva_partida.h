
#ifndef BOTON_NUEVA_PARTIDA_H
#define BOTON_NUEVA_PARTIDA_H


#include "protocolo.h"
#include "presionable.h"

class BotonNuevaPartida : public Presionable{
    bool* corriendo;
    Protocolo& protocolo;
    std::string& puerto;
    Ventana& ventana;
    
public:
    BotonNuevaPartida(Imagen* imagen,
                        bool* corriendo,
                        Protocolo& protocolo,
                        std::string& puerto,
                        Ventana& ventana);

    void presionar() override;
};



#endif

