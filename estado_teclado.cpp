#include <iostream>
#include "estado_teclado.h"

EstadoTeclado::EstadoTeclado(){
}

void EstadoTeclado::agregar_evento(SDL_KeyboardEvent evento) {
    estado_tecla[evento.keysym.sym] = evento.state;
}

bool EstadoTeclado::presionada(SDL_Keycode keyCode) {
    return (estado_tecla[keyCode] == SDL_PRESSED);
}

bool EstadoTeclado::liberada(SDL_Keycode keyCode) {
    return (estado_tecla[keyCode] == SDL_RELEASED);
}
