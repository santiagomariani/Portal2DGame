#ifndef ESTADO_TECLADO_H
#define ESTADO_TECLADO_H

#include <SDL2/SDL.h>
#include <map>

class EstadoTeclado {
private:
    std::map<SDL_Keycode, uint8_t> estado_tecla;

public:
    EstadoTeclado();
    // Agrega la tecla, con el estado correspondiente (presionada o liberada),
    // al mapa.
    void agregar_evento(SDL_KeyboardEvent evento);
    // Devuelve un booleano indicando si la tecla esta presionada.
    bool presionada(SDL_Keycode keyCode);
    // Devuelve un booleano indicando si la tecla esta liberada.
    bool liberada(SDL_Keycode keyCode);
    // Devuelve una referencia al mapa que contiene el estado de las teclas.
    std::map<SDL_Keycode, uint8_t>& obtenerMapa();
};

#endif //ESTADO_TECLADO_H
