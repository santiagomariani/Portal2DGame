
#include <iostream>
#include "boton_unirse_a_partida.h"


BotonUnirseAPartida::BotonUnirseAPartida(Imagen *imagen,
                                         bool *corriendo,
                                         Protocolo &protocolo,
                                         std::string &puerto):
                                         Presionable(imagen),
                                         corriendo(corriendo),
                                         protocolo(protocolo),
                                         puerto(puerto){

}

void BotonUnirseAPartida::presionar(){
    protocolo.enviarOpcionUnirsePartida();
    uint16_t cant = protocolo.recibirCantidad();
    std::cout << "cantidad de partidas a recibir: " << +cant << std::endl;
    std::map<int,std::string> partidas_activas;
    for (uint16_t i = 0; i < cant; i++){
        std::string puerto_partida = protocolo.recibirPuerto();
        std::cout << "puerto para unirse: " << i << ": " << puerto_partida << std::endl;
        //partidas_activas.emplace(i, std::move(puerto_partida));
        partidas_activas[i] = std::move(puerto_partida);
    }

    std::cout << "-ingresar numero: \n";
    int num;
    std::string puerto_partida;
    while (true){
        std::cin >> num;
        if (partidas_activas.count(num)){
            break;
        }
        std::cout << "dale pone uno bien\n";
    }
    puerto_partida = partidas_activas.at(num);
    std::cout << "puerto recibido\n";
    puerto.assign(puerto_partida);

    *corriendo = false;
}


