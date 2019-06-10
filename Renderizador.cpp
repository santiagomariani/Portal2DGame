//
// Created by santi on 09/06/19.
//

#include <SDL2/SDL_timer.h>
#include "Renderizador.h"
#include "ids.h"
#include "ViewChell.h"

Renderizador::Renderizador(SdlWindow &ventana,
        Camera &camara,
        ColaBloqueante<InfoCuerpo> &cola_renderizado,
        Renderizables &renderizables) :
        ventana(ventana),
        camara(camara),
        cola_renderizado(cola_renderizado),
        renderizables(renderizables),
        finalizo_fotograma(false) {
}

void Renderizador::renderizar() {
    InfoCuerpo ic;
    ventana.fill(0x33, 0x33, 0x33, 0xFF);
    camara.renderBg();
    while (!finalizo_fotograma) {
        cola_renderizado.pop(ic);
        if (ic.id == ID_CHELL) {
            camara.updateCamera(ic.dest); // tiene que ser la chell del cliente
            ((ViewChell *) renderizables.
            obtenerRenderizable(ic.id))->cambiarEstado(ic.estado,
                    ic.angulo*-1,
                    nullptr,
                    ic.flip);
        }
        camara.render(*renderizables.obtenerRenderizable(ic.id),
                ic.dest,
                ic.angulo*-1,
                nullptr,
                ic.flip);
    }
    ventana.render();
    finalizo_fotograma = false;
}

void Renderizador::finalizoFotograma() {
    finalizo_fotograma = true;
}
