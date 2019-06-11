#include <iostream>
#include "recibir_input.h"

#define RECIBIR_INPUT 1

RecibirInput::RecibirInput(std::queue<Input>& cola, Protocolo& protocolo):
                            cola(cola), protocolo(protocolo){
    this->terminar_proceso = false;
}

void RecibirInput::run(){
    while(!this->terminar_proceso){
        uint8_t msj = this->protocolo.recibirCodigoMensaje();
        if (msj != RECIBIR_INPUT){
            continue;
        }
        Input input = this->protocolo.recibirInput();
        this->cola.push(std::move(input));
    }
}

void RecibirInput::terminar(){
    this->terminar_proceso = true;
}

