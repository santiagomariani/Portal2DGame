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

#define FPS 60
#define TICKS_PER_FRAME 1000/FPS

class Renderizador {
private:
    Camera &camara;
    SdlWindow &ventana;
    Renderizables &renderizables;
    ColaBloqueante<InfoCuerpo> &cola_renderizado;
    bool finalizo_fotograma;
public:
    Renderizador(SdlWindow &ventana,
            Camera &camara,
            ColaBloqueante<InfoCuerpo> &cola_renderizado,
            Renderizables &renderizables);
    void renderizar();
    void finalizoFotograma();
};


#endif //RENDERIZADOR_H
