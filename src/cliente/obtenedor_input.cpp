#include <SDL2/SDL_events.h>
#include <iostream>
#include "obtenedor_input.h"
#include "estado_mouse.h"
#include "convertidor_coordenadas.h"
#include "input.h"
#include "ids_teclas.h"

ObtenedorInput::ObtenedorInput(ConvertidorCoordenadas &convertidor_coordenadas,
        Camara &camara,
        ColaBloqueante<Input> &cola_input,
        Ventana &ventana) :
        convertidor_coordenadas(convertidor_coordenadas),
        camara(camara),
        cola_input(cola_input),
        ventana(ventana){
}

std::map<int, int> ObtenedorInput::obtenerMapaTeclas(){
    std::map<int,int> teclas;
    teclas[SDLK_RIGHT] = DERECHA;
    teclas[SDLK_LEFT] = IZQUIERDA;
    teclas[SDLK_UP] = ARRIBA;
    teclas[SDLK_e] = TECLA_E;
    teclas[SDLK_RETURN] = ENTER;
    teclas[SDLK_LALT] = ALT_IZQ;
    return std::move(teclas);
}

bool ObtenedorInput::obtenerInput() {
    std::map<int,int> teclas = obtenerMapaTeclas();
    SDL_Event evento;
    estado_mouse.resetear();
    bool seguir = true;
    bool hay_input = false;
    while (SDL_PollEvent(&evento) != 0) {
        switch(evento.type) {
            case SDL_KEYDOWN:{
                SDL_KeyboardEvent& evento_teclado = (SDL_KeyboardEvent&) evento;
                int tecla = teclas[evento_teclado.keysym.sym];
                estado_teclado.agregar_evento(tecla, 1);
                hay_input = true;
                break;
            }
            case SDL_KEYUP:{
                SDL_KeyboardEvent& evento_teclado = (SDL_KeyboardEvent&) evento;
                int tecla = teclas[evento_teclado.keysym.sym];
                estado_teclado.agregar_evento(tecla, 0);
                hay_input = true;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                SDL_MouseButtonEvent& evento_mouse = 
                        (SDL_MouseButtonEvent&) evento;
                if ((evento_mouse.button) == SDL_BUTTON_LEFT){
                    b2Vec2 click = convertidor_coordenadas.sdlABox2D(
                            evento_mouse.x,
                            evento_mouse.y,
                            camara);
                    estado_mouse.agregarClickIzquierdo(click);
                }
                if ((evento_mouse.button) == SDL_BUTTON_RIGHT){
                    b2Vec2 click = convertidor_coordenadas.sdlABox2D(
                            evento_mouse.x,
                            evento_mouse.y,
                            camara);
                    estado_mouse.agregarClickDerecho(click);
                }
                hay_input = true;
                break;
            }
            case SDL_QUIT:
                seguir = false;
                Input input;
                input.chell_muerta = 1;
                cola_input.push(std::move(input));
                hay_input = false;
                break;
        }
    }
    if (estado_teclado.presionada(SDLK_LALT)
        && estado_teclado.presionada(SDLK_RETURN)) {
        ventana.cambiarPantalla();
    }

    if (hay_input) {
        Input input;
        input.estado_mouse = std::move(estado_mouse);
        input.estado_teclado = estado_teclado;
        // Pushear estado del mouse y del teclado en una cola.
        cola_input.push(std::move(input));
    }
    return seguir;
}
