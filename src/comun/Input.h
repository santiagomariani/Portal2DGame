//
// Created by santi on 09/06/19.
//

#ifndef INPUT_H
#define INPUT_H


#include "estado_teclado.h"
#include "estado_mouse.h"

struct Input {
    int id;
    EstadoTeclado estado_teclado;
    EstadoMouse estado_mouse;
    Input() = default;
    Input(const Input& otro):
            estado_teclado(otro.estado_teclado),
            estado_mouse(otro.estado_mouse){
        id = otro.id;
    }
    Input& operator=(const Input& otro){
        id = otro.id;
        estado_teclado = otro.estado_teclado;
        estado_mouse = otro.estado_mouse;
        return *this;
    }
};


#endif //INPUT_H
