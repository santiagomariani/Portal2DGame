//
// Created by santi on 09/06/19.
//

#include <iostream>
#include "ThInput.h"

ThInput::ThInput(ColaBloqueante<Input> &cola_input,
        Protocolo &protocolo, int id) :
        cola_input(cola_input),
        protocolo(protocolo),
        id(id){
}

void ThInput::run() {
    Input input;
    while (cola_input.pop(input)) {
        input.id = id;
        protocolo.enviarInput(input);
    }
}

void ThInput::terminar() {
    cola_input.finalizado();
}