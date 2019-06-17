#ifndef VENTANA_H
#define VENTANA_H

#include <cstdint>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_system.h>


class Ventana {
private:
    int ancho;
    int alto;
    SDL_Window *ventana;
    SDL_Renderer *renderizador;
    bool pantalla_completa;

public:
    // Se crea una ventana con el ancho y alto dado.
    Ventana(int ancho, int alto);
    // Pinta la ventana de un color dado en RGB y permite agregar una
    // transparencia (alpha).
    void pintar(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
    // Pinta la ventana de color gris.
    void pintar();
    // Renderiza en la ventana.
    void renderizar();
    // Permite cambiar de pantalla completa a pantalla redimensionable y
    // viceversa.
    void cambiarPantalla();
    // Devuelve el ancho de la ventana.
    int obtenerAncho();
    // Devuelve el alto de la ventana.
    int obtenerAlto();
    // Devuelve el renderizador.
    SDL_Renderer* obtenerRenderizador() const;
    ~Ventana();
};

#endif //VENTANA_H
