//
// Created by santi on 09/06/19.
//

#ifndef OBTENEDORINPUT_H
#define OBTENEDORINPUT_H


#include "CoordConverter.h"
#include "estado_teclado.h"
#include "estado_mouse.h"
#include "Camera.h"
#include "Input.h"
#include "ColaBloqueante.h"

class ObtenedorInput {
private:
    CoordConverter &coord_converter;
    Camera &camara;
    EstadoTeclado estado_teclado;
    EstadoMouse estado_mouse;
    ColaBloqueante<Input> &cola_input;
public:
    ObtenedorInput(CoordConverter &coord_converter,
            Camera &camara,
            ColaBloqueante<Input> &cola_input);
    bool obtenerInput();
};


#endif //OBTENEDORINPUT_H
