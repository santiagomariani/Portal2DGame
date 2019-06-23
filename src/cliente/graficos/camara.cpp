
#include "camara.h"

Camara::Camara(int ancho_camara,
        int alto_camara,
        Textura &fondo,
        Grabador &grabador) :
    ancho_camara(ancho_camara),
    alto_camara(alto_camara),
    fondo(fondo),
    grabador(grabador) {
    camara.x = 0;
    camara.y = 0;
    camara.w = ancho_camara;
    camara.h = alto_camara;
}

void Camara::renderizarFondo() {
    SDL_Rect dest = {0,
                     0,
                     camara.w,
                     camara.h};
    fondo.renderizar(nullptr, &dest);
    grabador.renderizarTexturaGrabador(fondo, nullptr, &dest);
}
void Camara::renderizar(Renderizable &renderizable,
                        SDL_Rect &destino,
                        double angulo,
                        SDL_Point *centro,
                        SDL_RendererFlip espejado) {
    if (!dentroDeCamara(destino)) {
        return;
    }
    SDL_Rect copia = destino;
    copia.x = destino.x - camara.x;
    copia.y = destino.y - camara.y;
    renderizable.renderizar(copia, angulo, centro, espejado);
    grabador.renderizarRenderizableGrabador(renderizable,
                                            copia,
                                            angulo,
                                            centro,
                                            espejado);
}

void Camara::actualizarCamara(SDL_Rect &destino) {
    int chellCenteredX = destino.x + (destino.w / 2);
    int chellCenteredY = destino.y + (destino.h / 2);
    camara.x = (chellCenteredX - (ancho_camara / 2));
    camara.y = (chellCenteredY - (alto_camara / 2));
    /*
    if (camara.x < 0) {
        camara.x = 0;
    }
    if (camara.y < 0) {
        camara.y = 0;
    }
    if (camara.x > ancho_camara - camara.w) {
        camara.x = ancho_camara - camara.w;
    }
    if (camara.y > alto_camara - camara.h) {
        camara.y = alto_camara - camara.h;
    }
    */
}

int Camara::obtenerX() {
    return camara.x;
}

int Camara::obtenerY() {
    return camara.y;
}

void Camara::reproducirSonidoChell(SonidosChell &sonidos_chell,
        SDL_Rect &destino,
        uint8_t estado) {
    if (!dentroDeCamara(destino)) {
        return;
    }
    sonidos_chell.reproducir(estado);
}

bool Camara::dentroDeCamara(SDL_Rect &destino) {
    if ((destino.x >= (camara.x + camara.w))
        || ((destino.x + destino.w - 1) < camara.x)) {
        return false;
    } else if ((destino.y >= (camara.y + camara.h))
        || ((destino.y + destino.h - 1) < camara.y)) {
        return false;
    }
    return true;
}
