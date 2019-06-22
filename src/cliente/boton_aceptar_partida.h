#ifndef BOTON_ACEPTAR_PARTIDA_H
#define BOTON_ACEPTAR_PARTIDA_H

#include "presionable.h"
#include "texto.h"
#include "protocolo.h"

class BotonAceptarPartida : public Presionable{
protected:
	bool* continuar;
	Texto mensaje;
	SDL_Color color = {0, 0, 0};
	std::string aceptar;
	std::string& puerto_elegido;
	std::string& puerto;
public:
	BotonAceptarPartida(Imagen* imagen, bool* continuar,
						Ventana& ventana, std::string& puerto_elegido,
						std::string& puerto);
	void render();
	void presionar() override;
	void mover(int offset_x, int offset_y);
};

#endif //BOTON_ACEPTAR_PARTIDA_H
