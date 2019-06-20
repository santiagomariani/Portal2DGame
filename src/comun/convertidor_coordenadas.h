
#ifndef CONVERTIDOR_COORDENADAS_H
#define CONVERTIDOR_COORDENADAS_H


#include <SDL2/SDL_rect.h>
#include <Box2D/Common/b2Math.h>

class ConvertidorCoordenadas {
private:
    const int CONVERSION = 80;
    int ancho_camara, alto_camara;
    
public:
    // Inicializa convertidor de coordenadas.
    ConvertidorCoordenadas(int ancho_camara, int alto_camara);
    // Convierte la posicion y el tamaño de un objeto en box2d a un rectangulo
    // de SDL con una posicion y tamaño dados en pixeles. Para esto se aplica
    // el factor de conversion.
    SDL_Rect box2DASDL(b2Vec2 posicion,
            float32 ancho_maximo,
            float32 alto_maximo);
    // Convierte una posicion en la camara (x, y) con x e y pixeles a una
    // posicion en box2d. Para esto se aplica el factor de conversion.
    b2Vec2 sdlABox2D(int x, int y, int x_camara, int y_camara);
};


#endif //CONVERTIDOR_COORDENADAS_H
