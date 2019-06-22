
#ifndef OBTENEDOR_INPUT_H
#define OBTENEDOR_INPUT_H

#include "convertidor_coordenadas.h"
#include "estado_teclado.h"
#include "estado_mouse.h"
#include "camara.h"
#include "input.h"
#include "cola_bloqueante.h"
#include "grabador.h"

class ObtenedorInput {
private:
    ConvertidorCoordenadas &convertidor_coordenadas;
    Camara &camara;
    EstadoTeclado estado_teclado;
    EstadoMouse estado_mouse;
    ColaBloqueante<Input> &cola_input;
    Ventana &ventana;
    Grabador &grabador;
    std::map<int, int> obtenerMapaTeclas();

public:
    ObtenedorInput(Camara &camara,
            ColaBloqueante<Input> &cola_input,
            Ventana &ventana,
            ConvertidorCoordenadas &convertidor_coordenadas,
            Grabador &grabador);
    // Obtiene el input y lo "pushea" en la cola de input para que luego un
    // hilo lo mande al servidor.
    bool obtenerInput();
};


#endif //OBTENEDOR_INPUT_H
