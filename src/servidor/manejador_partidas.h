

#ifndef MANEJADOR_PARTIDAS_H
#define MANEJADOR_PARTIDAS_H


#include <map>
#include "partida.h"

class ManejadorPartidas {
    std::map<std::string,Partida> partidas;
    std::vector<Thread*> threads_partidas;

public:
    ManejadorPartidas();
    void nuevaPartida(std::string puerto, Protocolo& protocolo);
    ~ManejadorPartidas() = default;

};


#endif //MANEJADOR_PARTIDAS_H
