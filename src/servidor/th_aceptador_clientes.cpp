
#include <SktAceptador.h>
#include "th_aceptador_clientes.h"
#include "th_opcion_partida.h"
#include "SocketError.h"

ThAceptadorClientes::ThAceptadorClientes(std::string puerto): puerto(puerto) {
}

void ThAceptadorClientes::run() {
    SktAceptador skt_aceptador(puerto);
    skt_aceptador.escucharClientes();

    while (true){
        try{
            Skt acept_skt = std::move(skt_aceptador.aceptarCliente());

            ThOpcionPartida* op = new ThOpcionPartida(std::move(acept_skt), partidas);

            this->threads_clientes.push_back(op);
            op->start();
        } catch(const SocketError &e){
            break;
        }
    }
}

void ThAceptadorClientes::terminar() {

}


