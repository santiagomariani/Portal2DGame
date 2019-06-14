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
	int lado_boton;
	int separacion;
	SDL_Rect destino_panel;
	std::vector<BotonBloque>* botones;
public:
	Botonera(Imagen* fondo, int ancho_v, int alto_v);
	void setBotones(std::vector<BotonBloque>* _botones);
	void render();
	bool colisiona(int x, int y);
	void recibirEvento(SDL_MouseButtonEvent& evento);
	void recibirEvento(SDL_MouseWheelEvent& evento);
};

#endif //BOTONERA
