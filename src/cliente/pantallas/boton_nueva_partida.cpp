#include <iostream>
#include "boton_nueva_partida.h"
#include "pantalla_elegir_mapa.h"

BotonNuevaPartida::BotonNuevaPartida(Imagen *imagen,
                                    bool *corriendo,
                                    Protocolo &protocolo,
                                    std::string& puerto,
                                    Ventana& ventana):
                                     Presionable(imagen),
                                     corriendo(corriendo),
                                     protocolo(protocolo),
                                     puerto(puerto),
                                     ventana(ventana){
}

void BotonNuevaPartida::presionar(){
    protocolo.enviarOpcionNuevaPartida();
    PantallaElegirMapa elegir_mapa(protocolo);
    if (!elegir_mapa(ventana)){
        return;
    }

    std::string puerto_partida = protocolo.recibirPuerto();
    puerto.assign(puerto_partida);
    
    *corriendo = false;
}
