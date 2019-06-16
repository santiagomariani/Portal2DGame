#include <iostream>
#include "recibir_input.h"
#include "SocketError.h"
#include "Protocolo.h"

RecibirInput::RecibirInput(ColaProtegidaInput& cola, Protocolo& protocolo):
                            cola(cola), protocolo(protocolo){
    this->terminar_proceso = false;
}

void RecibirInput::run(){
    while(!this->terminar_proceso){
        try{
            this->iteracion();
        } catch (SocketError& e){
            this->terminar_proceso = true;
            std::cout << "se desconecto un cliente.\n";
        }
    }
}

void RecibirInput::iteracion(){
    uint8_t msj = this->protocolo.recibirCodigoMensaje();
    Input input;
    if (msj == MSJ_CHELL_MUERTA){
        input.id =  this->protocolo.recibirId();
        input.chell_muerta = 1;
        this->cola.push(input);
    }
    else if (msj == MSJ_INPUT){
        input = this->protocolo.recibirInput();
        this->cola.push(input);
    }
}


void RecibirInput::terminar(){
    this->terminar_proceso = true;
}

