#ifndef FONDO_CONTINUO_H
#define FONDO_CONTINUO_H


#include <SDL2/SDL_rect.h>
#include "textura.h"
#include "ventana.h"

// Toma una porcion de una imagen y la recorre hacia la derecha
// al llegar al final vuelve al principio
class FondoContinuo{
	int ancho_f;
	int alto_f;
	int ancho_v;
	int alto_v;
	int velocidad;
	SDL_Rect area;
	SDL_Rect ventana;
    Textura& textura;
public:
	FondoContinuo(int ancho_f, int alto_f, int ancho_v, int alto_v,
				  int velocidad, Textura& textura);
	void render();
};

#endif //FONDO_CONTINUO_H