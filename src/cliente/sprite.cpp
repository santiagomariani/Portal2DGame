
#include "sprite.h"
#define VELOCIDAD_SPRITE 4

Sprite::Sprite(int ancho_imagen,
       int alto_imagen,
       int x,
       int y,
       unsigned int numero_imagenes,
       Textura &textura) :
       ancho_imagen(ancho_imagen),
       alto_imagen(alto_imagen),
       x(x),
       y(y),
       numero_imagenes(numero_imagenes),
       textura(textura) {
    imagenes_contadas = 0;
    contador_imagenes = 0;
    fuente.x = x;
    fuente.y = y;
    fuente.w = ancho_imagen;
    fuente.h = alto_imagen;
}

void Sprite::resetearAnimacion() {
    fuente.x = x;
    fuente.y = y;
    fuente.w = ancho_imagen;
    fuente.h = alto_imagen;
    imagenes_contadas = 0;
}

void Sprite::renderizar(SDL_Rect &destino,
                        double angulo,
                        SDL_Point *centro,
                        SDL_RendererFlip espejado) {
    if (numero_imagenes == 1) {
        textura.renderizar(&fuente, &destino, angulo, centro, espejado);
      return;
    }
    contador_imagenes++;
    if (imagenes_contadas == numero_imagenes) {
        resetearAnimacion();
    }
    textura.renderizar(&fuente, &destino, angulo, centro, espejado);
    if (contador_imagenes == VELOCIDAD_SPRITE) {
        imagenes_contadas++;
        contador_imagenes = 0;
        fuente.x += ancho_imagen + 1;
        if (fuente.x + fuente.w >= textura.obtenerAncho()) {
            fuente.x = x;
            fuente.y += alto_imagen + 1;
        }
    }
}

int Sprite::obtenerAnchoImagen() {
    return ancho_imagen;
}

int Sprite::obtenerAltoImagen() {
    return alto_imagen;
}

bool Sprite::finalizoAnimacion() {
    return imagenes_contadas == numero_imagenes;
}
