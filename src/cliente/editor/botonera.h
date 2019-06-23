#ifndef BOTONERA_H
#define BOTONERA_H

#include "imagen.h"
#include "boton_bloque.h"
#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include "cursor.h"

// Muestra la lista de botones que recibe por parametro de manera vertical
class Botonera{
	Imagen* fondo;
	int lado_boton;
	int separacion;
	SDL_Rect destino_panel;
	std::vector<BotonBloque>* botones;
public:
	Botonera(Imagen* fondo, int ancho_v, int alto_v);

	//Guarda la lista de botones 
	void setBotones(std::vector<BotonBloque>* _botones);

	//Muestra la lista de botones de manera vertical
	void render();

	// Chequea si la posicion (x, y) esta dentro de ella;
	bool colisiona(int x, int y);

	// Pasa el evento a todos los botones que contiene
	void recibirEvento(SDL_MouseButtonEvent& evento);

	// Mueve los botones para poder scrollear sobre ellos
	void recibirEvento(SDL_MouseWheelEvent& evento);
};

#endif //BOTONERA
