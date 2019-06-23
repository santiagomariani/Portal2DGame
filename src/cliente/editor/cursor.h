#ifndef CURSOR_H
#define CURSOR_H

#include "constructor_piezas.h"
#include "pieza.h"
#include "imagen.h"
#include <map>

class Cursor{
	ConstructorDePiezas constructor;
	int id;
	std::map<int, Imagen*>& imagenes;
	SDL_Rect actual_destino = {20, 20, 50, 50};
	int ultimo_click = -1;
	int anteultimo_click = -1;
	friend class MapaEditor;
public:
	Cursor(std::map<int, Imagen*>& imagenes, int id);

	// Guarda _id
	void setId(int _id);
	
	// Devuelve una pieza con los datos que contiene
	Pieza actual();

	// Muestra la ultima pieza clieckeada en la esquina de la pantalla
	void render();

	// Actualiza el ultimo y anteultimo click
	void click(int identificador);

	// Pone el ultimo y anteultimo click en -1
	void resetClick();

};


#endif //CURSOR