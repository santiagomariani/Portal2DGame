#ifndef BOTON_MAPA_H
#define BOTON_MAPA_H

#include "presionable.h"
#include "texto.h"

class BotonMapa : public Presionable{
	std::string& mapa_elegido;
	std::string& nombre_mapa;
	Texto mensaje;
	SDL_Color color = {0, 0, 0};
public:
	BotonMapa(Imagen* imagen, std::string& mapa_elegido, 
			  std::string& nombre_mapa, Ventana& ventana);
	void render();
	void presionar() override;
	void mover(int offset_x, int offset_y);
};

#endif //BOTON_MAPA
