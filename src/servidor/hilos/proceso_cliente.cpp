#include "proceso_cliente.h"
#include <cstdint>
#include <iostream>
#include "enviar_cuerpos.h"
#include "socket_error.h"
#include "recibir_input.h"

ProcesoCliente::ProcesoCliente(Skt socket, 
                            ColaProtegidaInput& cola_input,
                            ColaBloqueanteCuerpos* cola_cuerpos,
                            uint8_t id):
                            socket(std::move(socket)),
                            cola_input(cola_input),
                            cola_cuerpos(cola_cuerpos),
                            id(id){
    this->cancelado = false;
    this->terminar_proceso = false;
}

void ProcesoCliente::run(){
    Mensajero mensajero(socket);
    Protocolo protocolo(mensajero);

    try{
        protocolo.enviarId(id);
    } catch (SocketError& e){
        cancelado = true;
        return;
    }
    EnviarCuerpos* enviar_cuerpos = new EnviarCuerpos(cola_cuerpos, protocolo);
    RecibirInput* recibir_input = new RecibirInput(cola_input, protocolo);
    
    threads.push_back(enviar_cuerpos);
    threads.push_back(recibir_input);

    enviar_cuerpos->start();
    recibir_input->start();
}

void ProcesoCliente::terminar(){
    for (auto it=threads.begin(); it!=threads.end(); ++it){
        (*it)->terminar();
    }
    if (cancelado){
        return;
    }
    socket.cerrarCanales();
    socket.cerrarSocket();
    for (auto it=threads.begin(); it!=threads.end(); ++it){
        (*it)->join();
        delete *it;
    }
    threads.clear();
}

ProcesoCliente::~ProcesoCliente(){}
