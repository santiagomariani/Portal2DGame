#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

#include <iostream>

#include "SdlException.h"
#include "Ventana.h"


Ventana::Ventana(int ancho, int alto) :
        ancho(ancho), alto(alto), pantalla_completa(true) {
    int cod_error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (cod_error) {
        throw SdlException("Error en la inicialización: %s\n", SDL_GetError());
    }
    cod_error = SDL_CreateWindowAndRenderer(
        ancho, alto, SDL_RENDERER_ACCELERATED,
        &this->ventana, &this->renderizador);
    if (cod_error) {
        SDL_Quit();
        throw SdlException("Error al crear ventana: %s\n", SDL_GetError());
    }
    SDL_RenderSetLogicalSize(renderizador, ancho, alto);
    SDL_SetWindowResizable(ventana, SDL_TRUE);
    //SDL_SetWindowFullscreen(ventana, SDL_TRUE);
}

void Ventana::pintar(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
    SDL_SetRenderDrawColor(this->renderizador,r, g, b, alpha);
    SDL_RenderClear(this->renderizador);
}

void Ventana::pintar() {
    this->pintar(0x33, 0x33, 0x33, 0xFF);
}

void Ventana::renderizar() {
    SDL_RenderPresent(this->renderizador);
}

SDL_Renderer* Ventana::obtenerRenderizador() const {
    return this->renderizador;
}

Ventana::~Ventana() {
    if (this->ventana) {
        // ver si va esto.
        SDL_SetWindowFullscreen(ventana, SDL_FALSE);
        SDL_SetWindowSize(ventana, ancho, alto);
        SDL_RenderPresent(this->renderizador);
        // ^
        SDL_DestroyWindow(this->ventana);
        this->ventana = nullptr;
    }
    if (this->renderizador) {
        SDL_DestroyRenderer(this->renderizador);
        this->renderizador = nullptr;
    }
    SDL_Quit();
}

int Ventana::obtenerAncho() {
    return ancho;
}

int Ventana::obtenerAlto() {
    return alto;
}

void Ventana::cambiarPantalla() {
    if (pantalla_completa) {
        SDL_SetWindowFullscreen(ventana, SDL_FALSE);
        //SDL_SetWindowResizable(ventana, SDL_TRUE);
        pantalla_completa = false;
    } else {
        //SDL_SetWindowResizable(ventana, SDL_FALSE);
        SDL_SetWindowFullscreen(ventana, SDL_TRUE);
        pantalla_completa = true;
    }
}
