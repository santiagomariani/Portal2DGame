//
// Created by santi on 09/06/19.
//

#include <SDL2/SDL_timer.h>
#include "Renderizador.h"
#include "ids.h"
#include "ViewChell.h"
#include "msj_renderizado.h"

Renderizador::Renderizador(SdlWindow &ventana,
        Camera &camara,
        ColaBloqueante<MsjRenderizado> &cola_renderizado,
        std::map<uint8_t,Renderable*>& renderizables,
        int id_chell) :
        camara(camara),
        ventana(ventana),
        renderizables(renderizables),
        cola_renderizado(cola_renderizado),
        id_chell(id_chell){
}

void Renderizador::renderizar() {
    ventana.fill(0x33, 0x33, 0x33, 0xFF);
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
            ((ViewChell *) renderizables[ic.id])->cambiarEstado(ic.estado,
                    ic.angulo*-1,
                    nullptr,
                    ic.flip);
        }
        camara.render(*(renderizables[ic.id]),
                ic.dest,
                ic.angulo*-1,
                nullptr,
                ic.flip);
    }
    ventana.render();
}
