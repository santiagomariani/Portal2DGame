//
// Created by santi on 09/06/19.
//

#include <SDL2/SDL_timer.h>
#include "Renderizador.h"

Renderizador::Renderizador(SdlWindow &ventana,
        Renderizables &renderizables) :
    ventana(ventana),
    renderizables(renderizables),
    camara(ventana.obtenerAncho(), ventana.obtenerAlto()) {

}

void Renderizador::renderizar() {













    fpsTimer.start();
    ventana.fill(0x33, 0x33, 0x33, 0xFF);
    camara.renderBg();
    int cant  = protocolo.recibirCant();
    while (!(protocolo.termino())){
        struct InfoCuerpo cuerpo_info;
        protocolo.recibirCuerpo(cuerpo_info);

        SDL_Rect dest = cuerpo_info.dest;
        int id = cuerpo_info.id;
        int estado = cuerpo_info.estado;
        double angulo = cuerpo_info.angulo;

        if (id == ID_DISPARO) {
            camara.render(*texturas[id], dest, angulo);
        } else if (id == ID_PORTAL_AZUL || id == ID_PORTAL_NARANJA){
            camara.render(*texturas[id], dest, angulo);
        } else if (id == ID_BOLAENERGIA) {
            camara.render(*texturas[id], dest, angulo);
        } else if (id == ID_CHELL) {
            camara.updateCamera(dest); // tiene que ser la chell del cliente
            ((ViewChell*)texturas[id])->cambiarEstado(estado);
            SDL_RendererFlip flip = cuerpo_info.flip;
            camara.render(*texturas[id], dest, 0, nullptr, flip);
        } else {
            camara.render(*texturas[id], dest);
        }
    }
    ventana.render();

    int frameTicks = capTimer.getTicks();
    if (frameTicks < TICKS_PER_FRAME) {
        SDL_Delay(TICKS_PER_FRAME - frameTicks);
    }

}
