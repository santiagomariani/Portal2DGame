
#ifndef GRABADOR_H
#define GRABADOR_H


#include <SDL2/SDL_render.h>
#include "ventana.h"
#include "renderizable.h"
#include "th_video.h"
#include "textura.h"
#include "sprite.h"
#include <vector>
#include <cola_bloqueante.h>

class Grabador {
private:
    SDL_Texture* textura_video;
    Ventana &ventana;
    int ancho_buffer;
    int alto_buffer;
    std::vector<char> buffer;
    ColaBloqueante<std::vector<char>> cola_buffer;
    std::unique_ptr<ThVideo> th_video;
    bool grabando;
    Textura icono_grabacion;

public:
    Grabador(Ventana &ventana, int ancho_buffer, int alto_buffer);
    void iniciar_grabacion();
    void pintarFondoGrabador();
    void renderizarTexturaGrabador(Textura &textura,
            SDL_Rect *fuente = nullptr,
            SDL_Rect *destino = nullptr,
            double angulo = 0.0,
            SDL_Point *centro = nullptr,
            SDL_RendererFlip espejado = SDL_FLIP_NONE);
    void renderizarRenderizableGrabador(Renderizable &renderizable,
            SDL_Rect &destino,
            double angulo = 0.0,
            SDL_Point *centro = nullptr,
            SDL_RendererFlip espejado = SDL_FLIP_NONE);
    void renderizarIconoGrabacion();
    void finalizar_grabacion();
    void leerYEnviarPixeles();
    bool estaGrabando();
    virtual ~Grabador();
};


#endif //GRABADOR_H
