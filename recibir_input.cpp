#include "recibir_input.h"
#include "protocolo.h"
#include "input.h"

RecibirInput::RecibirInput(ColaBloqueante<Input>& cola, Protocolo& protocolo):
                            cola(cola), protocolo(protocolo){
    this->terminar = false;
}

void RecibirInput::run(){
    while(!this->terminar){
        uint8_t msj = this->protocolo.recibirMensaje();
        if (msj != RECIBIR_INPUT){
            continue;
        }
        struct Input input = this->protocolo.recibirInput();
        this->cola.push(input);
    }
    this->cola.finalizado();
}

void RecibirInput::terminar(){
    this->terminar = true;
}

RecibirInput::~RecibirInput(){}


