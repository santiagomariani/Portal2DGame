#ifndef BOTONERA_MAPAS_H
#define BOTONERA_MAPAS_H

#include "imagen.h"
#include "boton_mapa.h"
#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include "cursor.h"

// Muestra la lista de botones que recibe por parametro de manera vertical
class BotoneraMapas{
	Imagen* fondo;
	SDL_Rect& destino_panel;
	std::vector<BotonMapa>* botones;
public:
	BotoneraMapas(Imagen* fondo, SDL_Rect& destino);

	//Guarda la lista de botones 
	void setBotones(std::vector<BotonMapa>* _botones);

	//Muestra la lista de botones de manera vertical
	void render();

	// Chequea si la posicion (x, y) esta dentro de ella;
	bool colisiona(int x, int y);

	// Pasa el evento a todos los botones que contiene
	void recibirEvento(SDL_MouseButtonEvent& evento);

	// Mueve los botones para poder scrollear sobre ellos
	void recibirEvento(SDL_MouseWheelEvent& evento);
};

#endif //BOTONERA_MAPAS_H