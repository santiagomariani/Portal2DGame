
#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H

#include "ContadorTiempo.h"
#include "Ventana.h"
#include "renderizables.h"
#include "Camera.h"
#include "InfoCuerpo.h"
#include "ColaBloqueante.h"
#include "msj_renderizado.h"
#include "coleccion_vista_chells.h"
#include "SonidosChell.h"

#define FPS 60
#define TICKS_POR_FOTOGRAMA 1000/FPS

class Renderizador {
private:
    Camara &camara;
    Ventana &ventana;
    std::map<uint8_t,Renderizable*> &renderizables;
    ColaBloqueante<MsjRenderizado> &cola_renderizado;
    int id_chell;
    ColeccionVistaChells &coleccion_viewchells;
    SonidosChell sonidos_chell;

public:
    Renderizador(Ventana &ventana,
            Camara &camara,
            ColaBloqueante<MsjRenderizado> &cola_renderizado,
            std::map<uint8_t,Renderizable*> &renderizables,
            int id_chell,
            ColeccionVistaChells &coleccion_viewchells);
    // Obtiene la informacion de los cuerpos a renderizar, y los renderiza.
    // Ademas reproduce los sonidos de la Chell. Continua hasta que se recibe
    // el ultimo cuerpo a renderizar, momento en donde renderiza la ventana.
    void renderizar();
};


#endif //RENDERIZADOR_H
