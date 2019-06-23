
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "renderizador.h"
#include "ids.h"
#include "vista_chell.h"
#include "msj_renderizado.h"
#include "estado_chell.h"

Renderizador::Renderizador(Camara &camara,
                           ColaBloqueante<MsjRenderizado> &cola_renderizado,
                           ColeccionSprites &coleccion_sprites,
                           int id_chell,
                           ColeccionVistaChells &coleccion_viewchells,
                           Ventana &ventana,
                           Grabador &grabador) :
        camara(camara),
        ventana(ventana),
        coleccion_sprites(coleccion_sprites),
        cola_renderizado(cola_renderizado),
        id_chell(id_chell),
        coleccion_viewchells(coleccion_viewchells),
        chell_gano(false),
        grabador(grabador) {
}

void Renderizador::renderizar() {
    SDL_SetRenderTarget(ventana.obtenerRenderizador(), nullptr);
    ventana.pintar();
    camara.renderizarFondo();
    while (true) {
        MsjRenderizado msj;
        cola_renderizado.pop(msj);
        if (msj.ultimo){
            break;
        }
        InfoCuerpo ic;
        ic = msj.info_cuerpo;
        if (ic.id == ID_CHELL) {
            if (ic.id_chell == this->id_chell){
                camara.actualizarCamara(ic.destino);
            }
            VistaChell &view_chell = coleccion_viewchells.
                    obtenerVistaChell(ic.id_chell);
            
            view_chell.cambiarEstado(ic.estado,
                    ic.angulo*-1,
                    nullptr,
                    ic.espejado);
            camara.renderizar(view_chell,
                              ic.destino,
                              ic.angulo * -1,
                              nullptr,
                              ic.espejado);
            camara.reproducirSonidoChell(sonidos_chell, ic.destino, ic.estado);
            if (ic.estado == CHELL_GANO && !chell_gano){
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                         "Felicitaciones",
                         "Excelente. Has logrado el objetivo.",
                         nullptr);
                chell_gano = true;
            }
        } else {
            camara.renderizar(coleccion_sprites.obtenerSprite(ic.id),
                              ic.destino,
                              ic.angulo * -1,
                              nullptr,
                              ic.espejado);
        }
    }
    grabador.renderizarIconoGrabacion();
    if (grabador.estaGrabando()) {
        grabador.leerYEnviarPixeles();
    } else {
        ventana.renderizar();
    }
}
