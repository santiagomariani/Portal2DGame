//
// Created by santi on 08/06/19.
//

#include <iostream>
#include "estado_teclado.h"
#include "Protocolo.h"

int main() {
    int screen_width = 1200;
    int screen_height = 720;
    CoordConverter coord_converter(screen_width, screen_height);
    Protocolo protocolo(coord_converter);

    EstadoTeclado estado_teclado1;

    SDL_KeyboardEvent event1;
    event1.keysym.sym = SDLK_UP;
    event1.state = 1;
    SDL_KeyboardEvent event2;
    event2.keysym.sym = SDLK_RIGHT;
    event2.state = 0;
    SDL_KeyboardEvent event3;
    event3.keysym.sym = SDLK_DOWN;
    event3.state = 1;
    SDL_KeyboardEvent event4;
    event4.keysym.sym = SDLK_LEFT;
    event4.state = 0;
    SDL_KeyboardEvent event5;
    event5.keysym.sym = SDLK_e;
    event5.state = 1;

    estado_teclado1.agregar_evento(event1);
    estado_teclado1.agregar_evento(event2);
    estado_teclado1.agregar_evento(event3);
    estado_teclado1.agregar_evento(event4);
    estado_teclado1.agregar_evento(event5);

    auto &mapa_teclado1 = estado_teclado1.obtenerMapa();
    std::cout << "MAPA TECLADO 1: " << std::endl;
    for (auto it = mapa_teclado1.begin(); it != mapa_teclado1.end(); it++) {
        std::cout << "TECLA: " << it->first << " ESTADO: " << unsigned(it->second) << std::endl;
    }

    EstadoTeclado estado_teclado2;

    protocolo.enviarInput(estado_teclado1);
    protocolo.recibirInput(estado_teclado2);

    auto &mapa_teclado2 = estado_teclado2.obtenerMapa();

    std::cout << "MAPA TECLADO 2: " << std::endl;
    for (auto it = mapa_teclado2.begin(); it != mapa_teclado2.end(); it++) {
        std::cout << "TECLA: " << it->first << " ESTADO: " << unsigned(it->second) << std::endl;
    }
    return 0;
}
