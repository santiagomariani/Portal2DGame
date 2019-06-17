#include <SDL2/SDL_events.h>
#include <iostream>
#include "obtenedor_input.h"
#include "estado_mouse.h"
#include "convertidor_coordenadas.h"
#include "input.h"

ObtenedorInput::ObtenedorInput(ConvertidorCoordenadas &convertidor_coordenadas,
        Camara &camara,
        ColaBloqueante<Input> &cola_input,
        Ventana &ventana) :
        convertidor_coordenadas(convertidor_coordenadas),
        camara(camara),
        cola_input(cola_input),
        ventana(ventana)
    {
}

bool ObtenedorInput::obtenerInput() {
    SDL_Event evento;
    estado_mouse.resetear();
    bool seguir = true;
    bool hay_input = false;
    while (SDL_PollEvent(&evento) != 0) {
        switch(evento.type) {
            case SDL_KEYDOWN:{
                SDL_KeyboardEvent& evento_teclado = (SDL_KeyboardEvent&) evento;
                estado_teclado.agregar_evento(evento_teclado);
                hay_input = true;
                break;
            }
            case SDL_KEYUP:{
                SDL_KeyboardEvent& evento_teclado = (SDL_KeyboardEvent&) evento;
                estado_teclado.agregar_evento(evento_teclado);
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
