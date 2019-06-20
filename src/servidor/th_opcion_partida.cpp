
#include <skt.h>
#include "mensajero.h"
#include <protocolo.h>
#include <iostream>
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
    this->terminado = true;
}

void ThOpcionPartida::terminar() {
    std::cout << "terminado: " << terminado << std::endl;
    skt.cerrarCanales();
    skt.cerrarSocket();
    partidas.terminarPartidas();
}

ThOpcionPartida::~ThOpcionPartida() {
}

bool ThOpcionPartida::termino() {
    return this->terminado;
}


