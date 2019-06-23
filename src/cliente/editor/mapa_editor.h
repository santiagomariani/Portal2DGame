#ifndef MAPA_EDITOR_H
#define MAPA_EDITOR_H

#include <map>
#include <SDL2/SDL.h>
#include <vector>
#include "imagen.h"
#include "pieza.h"
#include "cursor.h"
#include <string>

// Representa un mapa del juego

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

	// Agrega una pieza en la posicion (x, y)
	void agregar(int x, int y, Pieza pieza);
	
	// Quita la pieza que hay en la posicion (x, y)
	void quitar(int x, int y);

	// Muestra las piezas que contiene
	void render();

	// Permite moverse por el mapa con las flechitas y entrar
	// en modo logico con la "l"
	void recibirEvento(SDL_KeyboardEvent& evento);

	// Actualiza el cursor con los datos de la pieza clickeada
	void recibirEvento(SDL_MouseButtonEvent& evento);

	// Se guarda en un archivo yaml con el nombre recibido
	std::string guardar();

	// Conecta dos piezas solo si son parte de la logica
	void conectar();
};

#endif //MAPA_EDITOR