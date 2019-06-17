#ifndef BOTON_JUGAR_H
#define BOTON_JUGAR_H

#include "presionable.h"

class BotonJugar : public Presionable{
	int* etapa;
	bool* corriendo;
public:
	BotonJugar(Imagen* imagen, int* etapa, bool* corriendo);

	// Abre el modo jugar del juego
	void presionar() override;
};

#endif //BOTON_JUGAR
