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
	void setId(int _id);
	Pieza actual();
	void render();
	void click(int identificador);
	void resetClick();

};


#endif //CURSOR