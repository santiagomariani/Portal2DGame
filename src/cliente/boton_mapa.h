#ifndef BOTON_MAPA_H
#define BOTON_MAPA_H

#include "presionable.h"

class BotonMapa{
	std::string& mapa_elegido;
	std::string& nombre_mapa;
public:
	BotonMapa(std::string& mapa_elegido, 
			  std::string& nombre_mapa);
	void presionar();
	void recibirEvento(SDL_MouseButtonEvent& click);
	void render();
	void colocar(int x, int y, int ancho, int alto);
};

#endif //BOTON_MAPA
