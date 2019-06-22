#include <skt.h>
#include "mensajero.h"
#include <protocolo.h>
#include <iostream>
#include <fstream>
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
    uint8_t opcion = protocolo.recibirCodigoMensaje();
    if (opcion == MSJ_OPCION_NUEVA_PARTIDA){
        partidas.nuevaPartida(protocolo);
    }
    if (opcion == MSJ_OPCION_UNIRSE_PARTIDA){
        // enviar puertos activos (esperando clientes)
        partidas.enviarPartidasEsperando(protocolo);
    }
    if (opcion == MSJ_CREAR_MAPA){
        std::string nombre_mapa = protocolo.recibirNombreMapa();
        nombre_mapa += ".yaml";
        std::string mapa_yaml = protocolo.recibirMapa();
        std::ofstream mapa(nombre_mapa);
        mapa << mapa_yaml;
        //breakuuuuu - chan - kawaiii;;
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


