#ifndef PIEZA_H
#define PIEZA_H

#include "imagen.h"
#include <SDL2/SDL.h>

class Pieza{
	int ancho;
	int alto;
	int identificador;
	bool logica;
protected:
	Imagen* imagen;
public:
	int id;
	Pieza();
	Pieza(int id, int ancho, int alto, Imagen* imagen, bool logica, int identificador);
	int getAncho();
	int getAlto();
	void render(SDL_Rect destino);
	virtual bool esLogica() {return logica;}
	int getIdentificador();
};
#endif //PIEZA
