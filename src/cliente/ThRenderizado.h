//
// Created by santi on 09/06/19.
//

#ifndef THRENDERIZADO_H
#define THRENDERIZADO_H


#include "ColaBloqueante.h"
#include "InfoCuerpo.h"
#include "Protocolo.h"
#include "Renderizador.h"
#include "Thread.h"

class ThRenderizado : public Thread {
private:
    ColaBloqueante<MsjRenderizado> &cola_renderizado;
    Protocolo &protocolo;
    Renderizador &renderizador;
    CoordConverter &coord_converter;
    bool terminado;
public:
    ThRenderizado(ColaBloqueante<MsjRenderizado> &cola_renderizado,
            Protocolo &protocolo,
            Renderizador &renderizador,
            CoordConverter &coord_converter);
    virtual void run();
    void terminar();
};


#endif //THRENDERIZADO_H
