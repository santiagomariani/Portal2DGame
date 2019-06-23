#include <SDL2/SDL_events.h>
#include <iostream>
#include "obtenedor_input.h"
#include "estado_mouse.h"
#include "convertidor_coordenadas.h"
#include "input.h"
#include "ids_teclas.h"

ObtenedorInput::ObtenedorInput(Camara &camara,
        ColaBloqueante<Input> &cola_input,
        Ventana &ventana,
        ConvertidorCoordenadas &convertidor_coordenadas,
        Grabador &grabador) :
        convertidor_coordenadas(convertidor_coordenadas),
        camara(camara),
        cola_input(cola_input),
        ventana(ventana),
        grabador(grabador) {
}

std::map<int, int> ObtenedorInput::obtenerMapaTeclas(){
    std::map<int,int> teclas;
    teclas[SDLK_RIGHT] = DERECHA;
    teclas[SDLK_LEFT] = IZQUIERDA;
    teclas[SDLK_UP] = ARRIBA;
    teclas[SDLK_e] = TECLA_E;
    teclas[SDLK_g] = TECLA_G;
    teclas[SDLK_f] = TECLA_F;
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
                int x_camara = camara.obtenerX();
                int y_camara = camara.obtenerY();
                if ((evento_mouse.button) == SDL_BUTTON_LEFT){
                    b2Vec2 click = convertidor_coordenadas.sdlABox2D(
                            evento_mouse.x,
                            evento_mouse.y,
                            x_camara,
                            y_camara);
                    estado_mouse.agregarClickIzquierdo(click);
                }
                if ((evento_mouse.button) == SDL_BUTTON_RIGHT){
                    b2Vec2 click = convertidor_coordenadas.sdlABox2D(
                            evento_mouse.x,
                            evento_mouse.y,
                            x_camara,
                            y_camara);
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
    if (estado_teclado.presionada(ALT_IZQ)
        && estado_teclado.presionada(ENTER)) {
        ventana.cambiarPantalla();
    }
    if (estado_teclado.presionada(TECLA_G)) {
        if (!grabador.estaGrabando()) {
            grabador.iniciar_grabacion();
        }
    }
    if (estado_teclado.presionada(TECLA_F)) {
        if (grabador.estaGrabando()) {
            grabador.finalizar_grabacion();
        }
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
