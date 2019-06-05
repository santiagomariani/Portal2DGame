#ifndef MAPA_EDITOR_H
#define MAPA_EDITOR_H

#include <map>
#include <SDL2/SDL.h>
#include <vector>
#include "imagen.h"
#include <string>

struct ParIdRect{
	int id;
	SDL_Rect destino;
};

class MapaEditor{
	SDL_Rect camara;
	std::map<int, std::map<int, ParIdRect>> mapa;
	std::map<int, Imagen*>& imagenes;
	int celda;

	int convertirPosicion(int a);
public:
	MapaEditor(std::map<int, Imagen*>& img, int ancho_cam, int alto_cam, int celda);
	void agregar(int id, int x, int y, int ancho, int alto);
	void quitar(int x, int y);
	void render();
	void recibirEvento(SDL_KeyboardEvent& evento);
	void guardar(std::string nombre);
};

#endif //MAPA_EDITOR