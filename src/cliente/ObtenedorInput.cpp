//
// Created by santi on 09/06/19.
//

#include <SDL2/SDL_events.h>
#include <iostream>
#include "ObtenedorInput.h"
#include "estado_mouse.h"
#include "CoordConverter.h"
#include "Input.h"

ObtenedorInput::ObtenedorInput(CoordConverter &coord_converter,
        Camera &camara,
        ColaBloqueante<Input> &cola_input) :
        coord_converter(coord_converter),
        camara(camara),
        cola_input(cola_input){
}

bool ObtenedorInput::obtenerInput() {
    SDL_Event event;
    estado_mouse.resetear();
    bool seguir = true;
    bool hay_input = false;
    while (SDL_PollEvent(&event) != 0 && seguir) {
        switch(event.type) {
            case SDL_KEYDOWN:{
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                estado_teclado.agregar_evento(keyEvent);
                hay_input = true;
                break;
            }
            case SDL_KEYUP:{
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                estado_teclado.agregar_evento(keyEvent);
                hay_input = true;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                SDL_MouseButtonEvent& mouseEvent = (SDL_MouseButtonEvent&) event;
                if ((mouseEvent.button) == SDL_BUTTON_LEFT){
                    b2Vec2 click = coord_converter.sdlToBox2D(mouseEvent.x, mouseEvent.y, camara);
                    estado_mouse.agregarClickIzquierdo(click);
                }
                if ((mouseEvent.button) == SDL_BUTTON_RIGHT){
                    b2Vec2 click = coord_converter.sdlToBox2D(mouseEvent.x, mouseEvent.y, camara);
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

    if (hay_input) {
        Input input;
        input.estado_mouse = std::move(estado_mouse);
        input.estado_teclado = estado_teclado;
        cola_input.push(std::move(input));
    }

    return seguir;
}
