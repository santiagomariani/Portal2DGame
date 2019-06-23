
#include <iostream>
#include <SDL2/SDL.h>
#include "th_input.h"
#include "socket_error.h"


ThInput::ThInput(ColaBloqueante<Input> &cola_input,
                 Protocolo &protocolo, uint8_t id) :
        cola_input(cola_input),
        protocolo(protocolo),
        id(id){
}

void ThInput::run() {
    Input input;
    while (cola_input.pop(input)) {
        input.id = id;
        if (input.chell_muerta == 1){
            protocolo.enviarChellMuerta(id);
            break;
        }
        try{
            protocolo.enviarInput(input);
        } catch (SocketError& e){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                         "Error",
                         "Hubo un error en la conexion",
                         NULL);
            break;
        }
    }
}

void ThInput::terminar() {
    cola_input.finalizado();
}
