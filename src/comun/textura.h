#ifndef TEXTURA_H
#define TEXTURA_H

#include <string>

#include "ventana.h"

class Textura {
private:
    SDL_Renderer *renderizador;
    SDL_Texture *textura;
    SDL_Texture* cargarTextura(const std::string &nombre_archivo);
    int ancho;
    int alto;

public:
    // Constructor por default.
    Textura();
    // Carga una textura en un SDL_Texture. Lanza una excepción si el nombre
    // de archivo es inválido o ocurrio algun error.
    Textura(const std::string &nombre_archivo, const Ventana &ventana);
    // Constructor por movimiento.
    Textura(Textura &&otro);
    // Operador asignacion por movimiento.
    Textura& operator=(Textura &&otro);
    // Una textura no es copiable.
    Textura(const Textura &otro) = delete;
    Textura& operator=(const Textura &otro) = delete;
    // Renderiza la textura cargada. Ademas puede rotar y espejar la imagen.
    // El rectangulo fuente selecciona que porcion de la imagen nos interesa,
    // mientras que el rectangulo destino indica donde se va a renderizar
    // y con que tamaño la porcion seleccionada con el primer rectangulo.
    int renderizar(const SDL_Rect *fuente = nullptr,
                   const SDL_Rect *destino = nullptr,
                   double angulo = 0.0,
                   SDL_Point *centro = nullptr,
                   SDL_RendererFlip espejado = SDL_FLIP_NONE) const;
    // Devuelve el ancho de la textura.
    int obtenerAncho();
    // Devuelve el alto de la textura.
    int obtenerAlto();
    // Setea un color de modulacion para la textura. Esto permite cambiar el
    // color de la imagen.
    void setearColorModulacion(uint8_t r, uint8_t g, uint8_t b);
    // Libera la memoria reservada por la textura.
    ~Textura();
};

#endif //TEXTURA_H
