#ifndef ESTADO_TECLADO_H
#define ESTADO_TECLADO_H

#include <map>

class EstadoTeclado {
private:
    //std::map<SDL_Keycode, uint8_t> estado_tecla;
    std::map<int,uint8_t> estado_tecla;

public:
    EstadoTeclado();
    // Agrega la tecla, con el estado correspondiente (presionada o liberada),
    // al mapa.
    void agregar_evento(int tecla, uint8_t estado);
    // Devuelve un booleano indicando si la tecla esta presionada.
    bool presionada(int tecla);
    // Devuelve un booleano indicando si la tecla esta liberada.
    bool liberada(int tecla);
    // Devuelve una referencia al mapa que contiene el estado de las teclas.
    std::map<int, uint8_t>& obtenerMapa();
};

#endif //ESTADO_TECLADO_H
