#include "proceso_cliente.h"
#include <cstdint>

ProcesoCliente::ProcesoCliente(Skt socket, 
                            ColaBloqueante& cola_input, 
                            ColaBloqueante& cola_cuerpos):
                            socket(socket),
                            cola_input(cola_input),
                            cola_cuerpos(cola_cuerpos){
    this->terminar = false;
}

void ProcesoCliente::run(){
    Mensajero mensajero(socket);
    Protocolo protocolo(mensajero);

    EnviarCuerpos* enviar_cuerpos = new EnviarCuerpos(cola_cuerpos, protocolo);
    RecibirInput* recibir_input = new RecibirInput(cola_input, protocolo);
    
    threads.push_back(enviar_cuerpos);
    threads.push_back(recibir_input);

    enviar_cuerpos->start();
    recibir_cuerpos->start();
}

void ProcesoCliente::terminar(){
    for (auto it=threads.begin(); it!=threads.end(); ++it){
        it->terminar();     
    }
}

ProcesoCliente::~ProcesoCliente(){}
