
#include <skt_aceptador.h>
#include "th_aceptador_clientes.h"
#include "th_opcion_partida.h"
#include "socket_error.h"

ThAceptadorClientes::ThAceptadorClientes(SktAceptador skt, std::string& puerto):
                                    skt_aceptador(std::move(skt)),
                                    partidas(puerto),
                                    terminado(false){
}

void ThAceptadorClientes::run() {

    skt_aceptador.escucharClientes();
    while (!this->terminado){
        try{
            Skt acept_skt = std::move(skt_aceptador.aceptarCliente());

            this->threads_clientes.emplace_back(new ThOpcionPartida(std::move(acept_skt), partidas));
            this->threads_clientes.back()->start();
        } catch(const SocketError &e){
            break;
        }
        for (size_t i = 0; i < threads_clientes.size(); ++i){
            if (threads_clientes[i]->termino()){
                threads_clientes[i]->join();
                threads_clientes[i].reset();
                threads_clientes.erase(threads_clientes.begin() + i);
                i -= 1;
            }
        }
        partidas.borrarPartidasTerminadas();
    }
}

void ThAceptadorClientes::terminar() {
    this->terminado = true;
    this->skt_aceptador.cerrarCanales();
    this->skt_aceptador.cerrarSocket();
    this->partidas.terminarPartidas();

    for (auto it=threads_clientes.begin(); it!=threads_clientes.end(); it++){
        //if (!(*it)->termino()) {
            (*it)->terminar();
            (*it)->join();
        //}
    }
}


