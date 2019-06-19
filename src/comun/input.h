
#ifndef INPUT_H
#define INPUT_H


#include "estado_teclado.h"
#include "estado_mouse.h"

struct Input {
    // Id del jugador.
    uint8_t id;
    EstadoTeclado estado_teclado;
    EstadoMouse estado_mouse;
    uint8_t chell_muerta = 0;
    Input() = default;
    Input(const Input& otro):
            estado_teclado(otro.estado_teclado),
            estado_mouse(otro.estado_mouse) {
        id = otro.id;
        chell_muerta = otro.chell_muerta;
    }
    Input& operator=(const Input& otro) {
        id = otro.id;
        estado_teclado = otro.estado_teclado;
        estado_mouse = otro.estado_mouse;
        chell_muerta = otro.chell_muerta;
        return *this;
    }
};


#endif //INPUT_H
