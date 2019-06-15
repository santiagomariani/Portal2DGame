//
// Created by santi on 09/06/19.
//

#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H

#include "Timer.h"
#include "Ventana.h"
#include "Renderizables.h"
#include "Camera.h"
#include "InfoCuerpo.h"
#include "ColaBloqueante.h"
#include "msj_renderizado.h"
#include "ColeccionViewChells.h"
#include "SonidosChell.h"

#define FPS 60
#define TICKS_PER_FRAME 1000/FPS

class Renderizador {
private:
    Camera &camara;
    Ventana &ventana;
    std::map<uint8_t,Renderable*> &renderizables;
    ColaBloqueante<MsjRenderizado> &cola_renderizado;
    int id_chell;
    ColeccionViewChells &coleccion_viewchells;
    SonidosChell sonidos_chell;
public:
    Renderizador(Ventana &ventana,
            Camera &camara,
            ColaBloqueante<MsjRenderizado> &cola_renderizado,
            std::map<uint8_t,Renderable*> &renderizables,
            int id_chell,
            ColeccionViewChells &coleccion_viewchells);
    void renderizar();
};


#endif //RENDERIZADOR_H
