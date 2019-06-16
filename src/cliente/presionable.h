#ifndef PRESIONABLE_H
#define PRESIONABLE_H

#include <SDL2/SDL.h>
#include "imagen.h"

class Presionable{
	Imagen* imagen;
protected:
	SDL_Rect destino; //El boton tiene un destino fijo y es unico
public:
	Presionable(Imagen* imagen);
	void colocar(int x, int y, int ancho, int alto);
	void recibirEvento(SDL_MouseButtonEvent& click);
	void render();
	virtual void presionar() = 0;
};

#endif //PRESIONABLE