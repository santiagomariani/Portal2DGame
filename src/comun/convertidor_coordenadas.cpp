
#include <iostream>
#include "CoordConverter.h"

ConvertidorCoordenadas::ConvertidorCoordenadas(int ancho_camara,
        int alto_camara) :
    ancho_camara(ancho_camara),
    alto_camara(alto_camara) {
}

SDL_Rect ConvertidorCoordenadas::box2DASDL(b2Vec2 posicion,
                                   float32 ancho_maximo,
                                   float32 alto_maximo) {
    SDL_Rect res = {int((posicion.x) * CONVERSION) + (ancho_camara / 2),
                    int((posicion.y) * CONVERSION * -1) + (alto_camara / 2),
                    int(ancho_maximo * CONVERSION),
                    int(alto_maximo* CONVERSION)};
    res.x -= int((ancho_maximo / 2) * CONVERSION);
    res.y -= int((alto_maximo / 2) * CONVERSION);
    return res;
}

b2Vec2 ConvertidorCoordenadas::sdlABox2D(int x, int y, Camara &camara) {
    b2Vec2 res;
    res.x = (x + camara.obtenerX() - ((float)ancho_camara / 2))
            / CONVERSION;
    res.y = ((y + camara.obtenerY() - ((float)alto_camara / 2))
            / CONVERSION) * -1;
    return res;
}
