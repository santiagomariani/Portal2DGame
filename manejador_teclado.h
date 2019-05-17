#ifndef MANEJADOR_TECLADO_H
#define MANEJADOR_TECLADO_H
#include <SDL2/SDL.h>
#include <map>

class ManejadorTeclado {
private:
    std::map<SDL_Keycode,int> estado_tecla;

public:
    ManejadorTeclado();

    void agregar_evento(SDL_KeyboardEvent evento);

    bool presionada(SDL_Keycode keyCode);

    bool liberada(SDL_Keycode keyCode);
};

#endif
