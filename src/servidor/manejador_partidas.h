#ifndef MANEJADOR_PARTIDAS_H
#define MANEJADOR_PARTIDAS_H

#include <map>
#include "partida.h"
#include "cargador_mapa.h"

// Clase para manejar varias partidas en simultaneo 

class ManejadorPartidas {
    std::vector<std::unique_ptr<Partida>> threads_partidas;
    std::list<CargadorMapa> mapas;
    std::string& puerto_server;
    std::string obtenerPuertoSiguiente();
    std::string sumarPuerto(std::string &puerto);
    std::mutex m;

    bool elegirMapa(Protocolo& protocolo, std::string& nombre_mapa);

public:
    explicit ManejadorPartidas(std::string& puerto_server);
    // Crea una nueva partida, devuelve si se creo correctamente.
    bool nuevaPartida(Protocolo& protocolo);
    void terminarPartidas();
    // Envia por el protocolo los puertos de las partidas
    // que estan todavia aceptando jugadores.
    bool enviarPartidasEsperando(Protocolo& protocolo);
    // Elimina los threads de las partidas que ya terminaron.
    void borrarPartidasTerminadas();
    ~ManejadorPartidas() = default;
};


#endif //MANEJADOR_PARTIDAS_H
