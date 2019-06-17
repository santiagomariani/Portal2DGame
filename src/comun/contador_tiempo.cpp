
#include <SDL2/SDL_timer.h>
#include "contador_tiempo.h"

ContadorTiempo::ContadorTiempo() : ticks_comienzo(0),
    ticks_pausado(0),
    comenzo(false),
    pausado(false) {
}

void ContadorTiempo::comenzar() {
    comenzo = true;
    pausado = false;
    ticks_comienzo = SDL_GetTicks();
    ticks_pausado = 0;
}

void ContadorTiempo::parar() {
    comenzo = false;
    pausado = false;
    ticks_comienzo = 0;
    ticks_pausado = 0;
}

void ContadorTiempo::pausar() {
    if (comenzo && !pausado) {
        pausado = true;
        ticks_pausado = SDL_GetTicks() - ticks_comienzo;
        ticks_comienzo = 0;
    }
}

void ContadorTiempo::despausar() {
    if (comenzo && pausado) {
        pausado = false;
        ticks_comienzo = SDL_GetTicks() - ticks_pausado;
        ticks_pausado = 0;
    }
}

uint32_t ContadorTiempo::obtenerTicks() {
    uint32_t tiempo = 0;
    if (comenzo) {
        if (pausado) {
            tiempo = ticks_pausado;
        } else {
            tiempo = SDL_GetTicks() - ticks_comienzo;
        }
    }
    return tiempo;
}
