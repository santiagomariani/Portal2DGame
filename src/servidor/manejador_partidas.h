

#ifndef MANEJADOR_PARTIDAS_H
#define MANEJADOR_PARTIDAS_H


#include <map>
#include "partida.h"
#include "cargador_mapa.h"

class ManejadorPartidas {
    //std::map<std::string,Partida> partidas;
    std::vector<std::unique_ptr<Partida>> partidas;
    std::vector<std::unique_ptr<Thread>> threads_partidas;
    std::list<CargadorMapa> mapas;

public:
    ManejadorPartidas();
    void nuevaPartida(std::string puerto, Protocolo& protocolo);
    void terminarPartidas();
    void enviarPartidasEsperando(Protocolo& protocolo);
    ~ManejadorPartidas() = default;
};


#endif //MANEJADOR_PARTIDAS_H
