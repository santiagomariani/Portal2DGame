#include <iostream>
#include "manejador_teclado.h"

ManejadorTeclado::ManejadorTeclado(){
}

void ManejadorTeclado::agregar_evento(SDL_KeyboardEvent evento) {
    estado_tecla[evento.keysym.sym] = evento.state;
}

bool ManejadorTeclado::presionada(SDL_Keycode keyCode) {
    return (estado_tecla[keyCode] == SDL_PRESSED);
}

bool ManejadorTeclado::liberada(SDL_Keycode keyCode) {
    return (estado_tecla[keyCode] == SDL_RELEASED);
}
