#ifndef BOTON_ESCRIBIR_H
#define BOTON_ESCRIBIR_H

#include "presionable.h"

class BotonEscribir : public Presionable{
	bool* escribir;
public:
	BotonEscribir(Imagen* imagen, bool* escribir);

	// Habilita al usuario escribir
	void presionar() override;
};

#endif //BOTON_ESCRIBIR