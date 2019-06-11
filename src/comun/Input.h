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
};


#endif //INPUT_H
