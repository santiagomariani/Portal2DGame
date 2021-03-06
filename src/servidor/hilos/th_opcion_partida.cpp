#include <skt.h>
#include "mensajero.h"
#include <protocolo.h>
#include <iostream>
#include <fstream>
#include <path.h>
#include "th_opcion_partida.h"
#include "manejador_partidas.h"

ThOpcionPartida::ThOpcionPartida(Skt socket, ManejadorPartidas& partidas):
                                 skt(std::move(socket)),
                                 partidas(partidas),
                                 terminado(false){
}

void ThOpcionPartida::run() {
    Mensajero mensajero(skt);
    Protocolo protocolo(mensajero);
    bool terminar = false;
    while (!terminar){
        uint8_t opcion = protocolo.recibirCodigoMensaje();
        if (opcion == MSJ_OPCION_NUEVA_PARTIDA){
            terminar = partidas.nuevaPartida(protocolo);
        }
        if (opcion == MSJ_OPCION_UNIRSE_PARTIDA){
            terminar = partidas.enviarPartidasEsperando(protocolo);
        }
        if (opcion == MSJ_CANCELAR){
            break;
        }
        if (opcion == MSJ_CREAR_MAPA){
            std::string nombre_mapa(std::string(MAPAS) + "mapas/");
            nombre_mapa += protocolo.recibirNombreMapa();
            nombre_mapa += ".yaml";
            std::string mapa_yaml = protocolo.recibirMapa();
            std::ofstream mapa(nombre_mapa);
            mapa << mapa_yaml;
            break;
        }
    }
    this->terminado = true;
}

void ThOpcionPartida::terminar() {
    skt.cerrarCanales();
    skt.cerrarSocket();
}

ThOpcionPartida::~ThOpcionPartida() {
}

bool ThOpcionPartida::termino() {
    return this->terminado;
}


