
#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H

#include "contador_tiempo.h"
#include "ventana.h"
#include "coleccion_sprites.h"
#include "camara.h"
#include "info_cuerpo.h"
#include "cola_bloqueante.h"
#include "msj_renderizado.h"
#include "coleccion_vista_chells.h"
#include "sonidos_chell.h"
#include "grabador.h"

#define FPS 60
#define TICKS_POR_FOTOGRAMA 1000/FPS

class Renderizador {
private:
    Camara &camara;
    Ventana &ventana;
    ColeccionSprites &coleccion_sprites;
    ColaBloqueante<MsjRenderizado> &cola_renderizado;
    int id_chell;
    ColeccionVistaChells &coleccion_viewchells;
    SonidosChell sonidos_chell;
    bool chell_gano;
    Grabador &grabador;

public:
    Renderizador(Camara &camara,
                 ColaBloqueante<MsjRenderizado> &cola_renderizado,
                 ColeccionSprites &coleccion_sprites,
                 int id_chell,
                 ColeccionVistaChells &coleccion_viewchells,
                 Ventana &ventana, Grabador &grabador);
    // Obtiene la informacion de los cuerpos a renderizar, y los renderiza.
    // Ademas reproduce los sonidos de la Chell. Continua hasta que se recibe
    // el ultimo cuerpo a renderizar, momento en donde renderiza la ventana.
    void renderizar();
};


#endif //RENDERIZADOR_H
