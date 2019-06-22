
#include <iostream>
#include "boton_unirse_a_partida.h"
#include "selector_partida.h"


BotonUnirseAPartida::BotonUnirseAPartida(Imagen *imagen,
                                         bool *corriendo,
                                         Protocolo &protocolo,
                                         std::string &puerto,
                                         Ventana& ventana):
                                         Presionable(imagen),
                                         corriendo(corriendo),
                                         protocolo(protocolo),
                                         puerto(puerto),
                                         ventana(ventana){

}

void BotonUnirseAPartida::presionar(){
    protocolo.enviarOpcionUnirsePartida();
    
    SelectorPartida s(protocolo);
    s(ventana, puerto);
    *corriendo = false;
}


