#include "partida.h"
#include "proceso_cliente.h"
#include "SocketError.h"
#include "cuerpo_a_enviar.h"
#include <iostream>

Partida::Partida(Fisica& fisica, SktAceptador skt): 
                fisica(fisica), skt_aceptador(std::move(skt)){
    this->continuar_juego = true;
    this->recibir_clientes = true;
}

void Partida::correrPartida(){ // 
    while (this->continuar_juego){
        struct Input input;
        if (!(this->cola_input.pop(input))){
            continue;
        }
        std::cout << "parece que popeo input\n";
        this->fisica.actualizar(input.estado_teclado, input.estado_mouse);

        std::vector<Cuerpo*> cuerpos = this->fisica.obtenerCuerpos();

        for (auto it=cuerpos.begin(); it!=cuerpos.end(); it++){
            for (auto c=colas_clientes.begin(); c!=colas_clientes.end(); c++){
                CuerpoAEnviar cuerpo_a_enviar;
                cuerpo_a_enviar.cuerpo = (*it);
                cuerpo_a_enviar.ultimo = false;
                (*c)->push(std::move(cuerpo_a_enviar));
            }
        }
        CuerpoAEnviar cuerpo_a_enviar;
        cuerpo_a_enviar.cuerpo = nullptr;
        cuerpo_a_enviar.ultimo = true;
        for (auto c=colas_clientes.begin(); c!=colas_clientes.end(); c++){
            (*c)->push(std::move(cuerpo_a_enviar));
            std::cout << "cuerpo pusheado\n";
        }
    }

    for (auto it=colas_clientes.begin(); it!=colas_clientes.end(); it++){
        (*it)->finalizado();
    }

    for (size_t i = 0; i < this->threads_clientes.size(); ++i){
        this->threads_clientes[i]->join();
        delete this->threads_clientes[i];
    }
}

void Partida::terminarPartida(){
    this->continuar_juego = false;
    for (auto it=threads_clientes.begin(); it!=threads_clientes.begin(); it++){
        (*it)->terminar();
    }
}


int Partida::recibirClientes(){ 
    int i = 0;
    //while (this->recibir_clientes){
        try{
            Skt acept_skt = std::move(this->skt_aceptador.aceptarCliente());
            ColaBloqueanteCuerpos* c = new ColaBloqueanteCuerpos();
            colas_clientes.push_back(c);
            ProcesoCliente* proceso = new ProcesoCliente(
                                            std::move(acept_skt),
                                            this->cola_input,
                                            colas_clientes[i]);
            this->threads_clientes.push_back(proceso);

            proceso->start();

        } catch(const SocketError &e){
            if (!this->recibir_clientes){ // si no fue forzado
                std::cerr << "Error accepting client:\n";
                std::cerr << e.what();
            }
            //break;
        }
        i++;
    //}
    return 0;
}

void Partida::terminarRecibirClientes(){
    this->recibir_clientes = false;
}


void Partida::comenzar(){
    this->recibirClientes();
    this->correrPartida();
}

Partida::~Partida(){}



