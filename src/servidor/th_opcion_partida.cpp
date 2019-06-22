
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
    bool terminar = false;
    while (!terminar){
        uint8_t opcion = protocolo.recibirCodigoMensaje();
        if (opcion == MSJ_OPCION_NUEVA_PARTIDA){
            terminar = partidas.nuevaPartida(protocolo);
        }
        if (opcion == MSJ_OPCION_UNIRSE_PARTIDA){
            // enviar puertos activos (esperando clientes)
            partidas.enviarPartidasEsperando(protocolo); // devolver bool para ver si sigue o no............................
            break;
        }
        if (opcion == MSJ_CANCELAR){
            break;
        }
    }
    std::cout << "terminado thOpcion\n";
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


