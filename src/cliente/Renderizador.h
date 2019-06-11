//
// Created by santi on 09/06/19.
//

#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H

#include "Timer.h"
#include "SdlWindow.h"
#include "Renderizables.h"
#include "Camera.h"
#include "InfoCuerpo.h"
#include "ColaBloqueante.h"
#include "msj_renderizado.h"

#define FPS 60
#define TICKS_PER_FRAME 1000/FPS

class Renderizador {
private:
    Camera &camara;
    SdlWindow &ventana;
    std::map<uint8_t,Renderable*> &renderizables;
    ColaBloqueante<MsjRenderizado> &cola_renderizado;
public:
    Renderizador(SdlWindow &ventana,
            Camera &camara,
            ColaBloqueante<MsjRenderizado> &cola_renderizado,
            std::map<uint8_t,Renderable*> &renderizables);
    void renderizar();
};


#endif //RENDERIZADOR_H
