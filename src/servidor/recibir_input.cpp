#include <iostream>
#include "recibir_input.h"

#define RECIBIR_INPUT 1

RecibirInput::RecibirInput(ColaProtegidaInput& cola, Protocolo& protocolo):
                            cola(cola), protocolo(protocolo){
    this->terminar_proceso = false;
}

void RecibirInput::run(){
    while(!this->terminar_proceso){
        uint8_t msj = this->protocolo.recibirCodigoMensaje();
        if (msj != RECIBIR_INPUT){
            continue;
        }
        Input input;
        input = this->protocolo.recibirInput();
        this->cola.push(input);
    }
}

void RecibirInput::terminar(){
    this->terminar_proceso = true;
}

