
#ifndef OBTENEDOR_INPUT_H
#define OBTENEDOR_INPUT_H

#include "convertidor_coordenadas.h"
#include "estado_teclado.h"
#include "estado_mouse.h"
#include "camara.h"
#include "input.h"
#include "cola_bloqueante.h"

class ObtenedorInput {
private:
    ConvertidorCoordenadas &convertidor_coordenadas;
    Camara &camara;
    EstadoTeclado estado_teclado;
    EstadoMouse estado_mouse;
    ColaBloqueante<Input> &cola_input;
    Ventana &ventana;

    std::map<int, int> obtenerMapaTeclas();

public:
    ObtenedorInput(ConvertidorCoordenadas &convertidor_coordenadas,
            Camara &camara,
            ColaBloqueante<Input> &cola_input,
            Ventana &ventana);
    // Obtiene el input y lo "pushea" en la cola de input para que luego un
    // hilo lo mande al servidor.
    bool obtenerInput();
};


#endif //OBTENEDOR_INPUT_H
