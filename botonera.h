#ifndef BOTONERA_H
#define BOTONERA_H

#include "imagen.h"
#include "boton_bloque.h"
#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include "cursor.h"

class Botonera{
	Imagen* fondo;
	int ancho_v;
	int alto_v;
	SDL_Rect destino_panel;
	std::vector<BotonBloque> botones;
	int division;
public:
	Botonera(std::map<int, Imagen*>& imagenes, Cursor& cursor, Imagen* fondo,
			 int ancho_v, int alto_v, int celda);
	void render();
	bool colisiona(int x, int y);
	void recibirEvento(SDL_MouseButtonEvent& evento);
	void recibirEvento(SDL_MouseWheelEvent& evento);
};

#endif //BOTONERA
