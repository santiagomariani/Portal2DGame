
#ifndef SPRITE_H
#define SPRITE_H


#include "Textura.h"
#include "Ventana.h"
#include "Renderizable.h"

// Permite renderizar una animacion. Cada vez que se llama a renderizar se
// renderiza una imagen. Una animacion (Sprite) puede tener 1 o mas imagenes.
// Al renderizar una imagen, se avanza a la siguiente y la proxima vez que se
// llame a renderizar se renderiza la imagen siguiente.

class Sprite : public Renderizable {
private:
    int ancho_imagen;
    int alto_imagen;
    int x, y;
    int numero_imagenes;
    int imagenes_contadas;
    int contador_imagenes;
    SDL_Rect fuente;
    Textura &textura;

public:
    // Inicializa un Sprite.
    Sprite(int ancho_imagen,
           int alto_imagen,
           int x,
           int y,
           unsigned int numero_imagenes,
           Textura &textura);

    // Reinicia la animacion (vuelve a la primer imagen).
    void resetearAnimacion();

    // Renderiza la imagen actual, con angulo y espejado deseado. Ademas se
    // puede elegir donde renderizar (con el rectangulo destino).
    void renderizar(SDL_Rect &destino,
                    double angulo,
                    SDL_Point *centro,
                    SDL_RendererFlip espejado) override;

    // Devuelve el ancho de una imagen (No textura).
    int obtenerAnchoImagen();
    // Devuelve el alto de una imagen.
    int obtenerAltoImagen();
    // Devuelve un booleano indicando si termino la animacion.
    bool finalizoAnimacion();
    // Destructor por default.
    ~Sprite() = default;
};


#endif //SPRITE_H
