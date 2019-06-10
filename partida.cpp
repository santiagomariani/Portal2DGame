#include "partida.h"
#include "proceso_cliente.h"
#include "SocketError.h"

Partida::Partida(Fisica& fisica, SktAceptador skt): 
                fisica(fisica), skt(std::move(skt)){
    this->continuar_juego = true;
    this->recibir_clientes = true;
}

void Partida::correrPartida(){ // 
    while (this->continuar_juego){
        struct Input input;
        if (!(this->cola_input.pop(input))){
            continue;
        }
        this->fisica.actualizar(input.estado_teclado, estado_input.mouse);

        std::vector<Cuerpo*> cuerpos = this->fisica.obtenerCuerpos();

        for (auto it=cuerpos.begin(); it!=cuerpos.end(); it++){
            for (auto c=colas_clientes.begin(); c!=colas_clientes.end(); c++){
                c->push(*it);
            }
        }
    }

    for (auto it=colas_clientes.begin(); it!=colas_clientes.end(); it++){
        it->finalizado();
    }

    for (size_t i = 0; i < this->threads_clientes.size(); ++i){
        this->threads_clientes[i]->join();
        delete this->threads_clientes[i];
    }
}

void Partida::terminarPartida(){
    this->continuar_juego = false;
    for (auto it=threads_clientes.begin(); it!=threads_clientes.begin(); it++){
        it->terminar();
    }
}


int Partidas::recibirClientes(){ 
    int i = 0;
    //while (this->recibir_clientes){
        try{
            Skt acept_skt = std::move(this->skt.aceptarClientes());
            colas_clientes.emplace_back();
            ProcesoCliente* proceso = new ProcesoCliente(
                                            std::move(acept_skt),
                                            this->cola_input.
                                            colas_clientes[i]);
            this->threads_clientes.push_back(proceso);

            proceso->start();

        } catch(const SocketError &e){
            if (!this->recibir_clientes){ // si no fue forzado
                std::cerr << "Error accepting client:\n";
                std::cerr << e.what();
            }
            break;
        }
        i++;
    //}
    return 0;
}

void Partida::terminarRecibirClientes(){
    this->recibir_clientes = false;
}


void Partida::comezar(){
    this->recibirClientes();
    this->correrPartida();
}

