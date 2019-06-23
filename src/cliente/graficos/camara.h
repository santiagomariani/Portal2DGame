
#ifndef CAMARA_H
#define CAMARA_H


#include <SDL2/SDL_rect.h>
#include "renderizable.h"
#include "textura.h"
#include "sonidos_chell.h"
#include "grabador.h"

class Camara {
private:
    int ancho_camara;
    int alto_camara;
    SDL_Rect camara;
    Textura &fondo;
    Grabador &grabador;
    // Devuelve un booleano indicando si el objeto esta dentro de la camara.
    bool dentroDeCamara(SDL_Rect &destino);

public:
    // Inicializa camara.
    Camara(int ancho_camara,
            int alto_camara,
            Textura &fondo,
            Grabador &grabador);
    // Renderiza el renderizable, con los parametros especificados, si lo que
    // se quiere renderizar esta dentro de la camara.
    void renderizar(Renderizable &renderizable,
                    SDL_Rect &destino,
                    double angulo = 0.0,
                    SDL_Point *centro = nullptr,
                    SDL_RendererFlip espejado = SDL_FLIP_NONE);
    // Renderiza el fondo.
    void renderizarFondo();
    // Reproduce el sonido, si el estado tiene un sonido asignado y si la
    // Chell esta dentro de la camara.
    void reproducirSonidoChell(SonidosChell &sonidos_chell,
            SDL_Rect &destino,
            uint8_t estado);
    // Actualiza la camara con la ubicacion de la Chell del cliente asociado a
    // la camara.
    void actualizarCamara(SDL_Rect &destino);
    // Devuelve el X de la camara.
    int obtenerX();
    // Devuelve el Y de la camara.
    int obtenerY();
};


#endif //CAMARA_H
