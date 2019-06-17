
#include <iostream>
#include "th_input.h"

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
        if (input.chell_muerta == 1){
            std::cout << "enviando chell muerta\n";
            protocolo.enviarChellMuerta(id);
            break;
        }
        protocolo.enviarInput(input);
    }
}

void ThInput::terminar() {
    cola_input.finalizado();
}
