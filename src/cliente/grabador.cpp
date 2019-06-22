
#include <SDL2/SDL_messagebox.h>
#include <iostream>
#include "grabador.h"

Grabador::Grabador(Ventana &ventana,
        int ancho_buffer,
        int alto_buffer) :
        textura_video(nullptr),
        ventana(ventana),
        ancho_buffer(ancho_buffer),
        alto_buffer(alto_buffer),
        th_video(nullptr),
        grabando(false) {
}

void Grabador::iniciar_grabacion() {
    grabando = true;
    th_video.reset(new ThVideo(cola_buffer, ancho_buffer, alto_buffer));
    textura_video = SDL_CreateTexture(ventana.obtenerRenderizador(),
                                      SDL_PIXELFORMAT_RGB24,
                                      SDL_TEXTUREACCESS_TARGET,
                                      ancho_buffer,
                                      alto_buffer);
    buffer.resize((unsigned long)ancho_buffer*alto_buffer*3);
    th_video->start();
}

void Grabador::pintarFondoGrabador() {
    if (estaGrabando()) {
        SDL_SetRenderTarget(ventana.obtenerRenderizador(), textura_video);
        ventana.pintar();
        SDL_SetRenderTarget(ventana.obtenerRenderizador(), nullptr);
    }
}

void Grabador::renderizarTexturaGrabador(Textura &textura,
        SDL_Rect *fuente,
        SDL_Rect *destino,
        double angulo,
        SDL_Point *centro,
        SDL_RendererFlip espejado) {
    if (estaGrabando()) {
        SDL_SetRenderTarget(ventana.obtenerRenderizador(), textura_video);
        textura.renderizar(fuente, destino, angulo, centro, espejado);
        SDL_SetRenderTarget(ventana.obtenerRenderizador(), nullptr);
    }
}

void Grabador::renderizarRenderizableGrabador(Renderizable &renderizable,
                                              SDL_Rect &destino,
                                              double angulo,
                                              SDL_Point *centro,
                                              SDL_RendererFlip espejado) {
    if (estaGrabando()) {
        SDL_SetRenderTarget(ventana.obtenerRenderizador(), textura_video);
        renderizable.renderizar(destino, angulo, centro, espejado);
        SDL_SetRenderTarget(ventana.obtenerRenderizador(), nullptr);
    }
}

void Grabador::leerYEnviarPixeles() {
    SDL_SetRenderTarget(ventana.obtenerRenderizador(),
            textura_video);
    ventana.renderizar();
    int res = SDL_RenderReadPixels(ventana.obtenerRenderizador(),
                                   nullptr,
                                   SDL_PIXELFORMAT_RGB24,
                                   buffer.data(),
                                   ancho_buffer * 3);
    if (res) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "RendererReadPixels error",
                                 SDL_GetError(),
                                 nullptr);
    }
    cola_buffer.push(buffer);
    buffer.resize((unsigned long)ancho_buffer*alto_buffer*3);
    SDL_SetRenderTarget(ventana.obtenerRenderizador(),
                        nullptr);
}

void Grabador::finalizar_grabacion() {
    if (textura_video) {
        SDL_DestroyTexture(textura_video);
        textura_video = nullptr;
        th_video->terminar();
        th_video->join();
        grabando = false;
        buffer.clear();
    }
}

bool Grabador::estaGrabando() {
    return grabando;
}

Grabador::~Grabador() {
    if (textura_video) {
        SDL_DestroyTexture(textura_video);
        textura_video = nullptr;
    }
}
