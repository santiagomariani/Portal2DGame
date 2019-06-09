//
// Created by santi on 09/06/19.
//

#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H

#include "Timer.h"
#include "SdlWindow.h"
#include "Renderizables.h"
#include "Camera.h"

#define FPS 60
#define TICKS_PER_FRAME 1000/FPS

class Renderizador {
private:
    Timer fpsTimer;
    Timer capTimer;
    Camera camara;
    SdlWindow &ventana;
    Renderizables &renderizables;
public:
    Renderizador(SdlWindow &ventana);
    void renderizar();
};


#endif //RENDERIZADOR_H
