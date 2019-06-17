#ifndef FONDO_CONTINUO_H
#define FONDO_CONTINUO_H


#include "textura.h"
#include "ventana.h"

class FondoContinuo{
	int ancho_f;
	int alto_f;
	int ancho_v;
	int alto_v;
	int velocidad;
	SDL_Rect area;
	SDL_Rect ventana;
	SdlTexture& textura;
public:
	FondoContinuo(int ancho_f, int alto_f, int ancho_v, int alto_v,
				  int velocidad, SdlTexture& textura);
	void render();
};

#endif //FONDO_CONTINUO_H