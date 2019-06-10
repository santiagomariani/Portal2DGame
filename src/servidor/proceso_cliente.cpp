#include "proceso_cliente.h"
#include <cstdint>
#include "enviar_cuerpos.h"
#include "recibir_input.h"

ProcesoCliente::ProcesoCliente(Skt socket, 
                            ColaBloqueante<Input>& cola_input, 
                            ColaBloqueanteCuerpos* cola_cuerpos):
                            socket(std::move(socket)),
                            cola_input(cola_input),
                            cola_cuerpos(cola_cuerpos){
    this->terminar_proceso = false;
}

void ProcesoCliente::run(){
    Mensajero mensajero(socket);
    Protocolo protocolo(mensajero);

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
}

ProcesoCliente::~ProcesoCliente(){}
