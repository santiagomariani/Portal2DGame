//
// Created by santi on 09/06/19.
//

#include <SDL2/SDL_timer.h>
#include "Renderizador.h"
#include "ids.h"
#include "ViewChell.h"
#include "msj_renderizado.h"

Renderizador::Renderizador(Ventana &ventana,
        Camera &camara,
        ColaBloqueante<MsjRenderizado> &cola_renderizado,
        std::map<uint8_t,Renderable*>& renderizables,
        int id_chell,
        ColeccionViewChells &coleccion_viewchells) :
        camara(camara),
        ventana(ventana),
        renderizables(renderizables),
        cola_renderizado(cola_renderizado),
        id_chell(id_chell),
        coleccion_viewchells(coleccion_viewchells) {
}

void Renderizador::renderizar() {
    ventana.pintar(0x33, 0x33, 0x33, 0xFF);
    camara.renderBg();
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
                camara.updateCamera(ic.dest); // tiene que ser la chell del cliente
            }
            ViewChell &view_chell = coleccion_viewchells.obtenerViewChell(ic.id_chell);
            
            view_chell.cambiarEstado(ic.estado,
                    ic.angulo*-1,
                    nullptr,
                    ic.flip);
            camara.render(view_chell,
                    ic.dest,
                    ic.angulo*-1,
                    nullptr,
                    ic.flip);
            camara.reproducirSonidoChell(sonidos_chell, ic.dest, ic.estado);
        } else {
            camara.render(*(renderizables[ic.id]),
                          ic.dest,
                          ic.angulo*-1,
                          nullptr,
                          ic.flip);
        }
    }
    ventana.renderizar();
}
