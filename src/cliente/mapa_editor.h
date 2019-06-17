#ifndef MAPA_EDITOR_H
#define MAPA_EDITOR_H

#include <map>
#include <SDL2/SDL.h>
#include <vector>
#include "imagen.h"
#include "pieza.h"
#include "cursor.h"
#include <string>

class MapaEditor{
	SDL_Rect camara;
	std::map<int, std::map<int, Pieza>> mapa;
	std::map<int, int> conexiones;
	int celda;
	bool estado_logico;
	Cursor& cursor;

	int convertirPosicion(int a);
public:
	MapaEditor(int ancho_cam, int alto_cam, int celda, Cursor& cursor);
	void agregar(int x, int y, Pieza pieza);
	void quitar(int x, int y);
	void render();
	void recibirEvento(SDL_KeyboardEvent& evento);
	void recibirEvento(SDL_MouseButtonEvent& evento);
	void guardar(std::string& nombre);
	void conectar();
};

#endif //MAPA_EDITOR