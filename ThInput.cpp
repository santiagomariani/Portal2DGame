//
// Created by santi on 09/06/19.
//

#include "ThInput.h"

ThInput::ThInput(ColaBloqueante<Input> &cola_input,
        Protocolo &protocolo) :
        cola_input(cola_input),
        protocolo(protocolo) {
}

void ThInput::run() {
    Input input;
    while (cola_input.pop(input)) {
        protocolo.enviarInput(input);
    }
}

void ThInput::terminar() {
    cola_input.finalizado();
}
