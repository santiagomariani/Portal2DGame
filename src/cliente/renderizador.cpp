
#include <SDL2/SDL_timer.h>
#include "Renderizador.h"
#include "ids.h"
#include "VistaChell.h"
#include "msj_renderizado.h"

Renderizador::Renderizador(Ventana &ventana,
        Camara &camara,
        ColaBloqueante<MsjRenderizado> &cola_renderizado,
        std::map<uint8_t,Renderizable*>& renderizables,
        int id_chell,
        ColeccionVistaChells &coleccion_viewchells) :
        camara(camara),
        ventana(ventana),
        renderizables(renderizables),
        cola_renderizado(cola_renderizado),
        id_chell(id_chell),
        coleccion_viewchells(coleccion_viewchells) {
}

void Renderizador::renderizar() {
    ventana.pintar(0x33, 0x33, 0x33, 0xFF);
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
        } else {
            camara.renderizar(*(renderizables[ic.id]),
                              ic.destino,
                              ic.angulo * -1,
                              nullptr,
                              ic.espejado);
        }
    }
    ventana.renderizar();
}
