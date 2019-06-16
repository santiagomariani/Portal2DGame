
#include <iostream>
#include "boton_nueva_partida.h"

BotonNuevaPartida::BotonNuevaPartida(Imagen *imagen,
                                    bool *corriendo,
                                    Protocolo &protocolo,
                                    std::string& puerto):
                                     Presionable(imagen),
                                     corriendo(corriendo),
                                     protocolo(protocolo),
                                     puerto(puerto){

}

void BotonNuevaPartida::presionar(){
    std::cout << "enviando nueva partida request\n";
    protocolo.enviarOpcionNuevaPartida();
    std::cout << "enviado req\n";
    //std::string puerto_partida("8081");
    //protocolo.enviarPuerto(puerto_partida);
    //uint8_t respuesta = protocolo.recibirCodigoMensaje();
    //if (respuesta != MSJ_PARTIDA_CREADA){
      //  puerto.assign(""); // error al crear el socket en el servidor
    //}
    std::string puerto_partida = protocolo.recibirPuerto();
    std::cout << "puerto recibido\n";
    puerto.assign(puerto_partida);
    
    *corriendo = false;
}
