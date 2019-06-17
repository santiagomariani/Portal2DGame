#ifndef IMAGEN_H
#define IMAGEN_H

#include "textura.h"

class Imagen{
protected:
	int alto;
	int ancho;
	SDL_Rect area;
	Textura* textura;
public:
	Imagen();
	Imagen(int area_x, int area_y, int ancho, int alto,
		   Textura* textura);
	Imagen(Imagen&& otra);
	void render(SDL_Rect& destino);
};

#endif //IMAGEN