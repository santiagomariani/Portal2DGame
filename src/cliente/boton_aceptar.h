#ifndef BOTON_ACEPTAR_H
#define BOTON_ACEPTAR_H

#include "presionable.h"
#include "texto.h"
#include "protocolo.h"

class BotonAceptar : public Presionable{
protected:
	bool* continuar;
	Texto mensaje;
	SDL_Color color = {0, 0, 0};
	std::string aceptar;
	Protocolo& protocolo;
	std::string& mapa_elegido;
public:
	BotonAceptar(Imagen* imagen, bool* continuar, Ventana& ventana,
					Protocolo& protocolo,
					std::string& mapa_elegido);
	void render();
	void presionar() override;
	void mover(int offset_x, int offset_y);
};

#endif //BOTON_ACEPTAR
