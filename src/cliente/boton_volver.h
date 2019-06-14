#ifndef BOTON_VOLVER_H
#define BOTON_VOLVER_H

#include "presionable.h"

class BotonVolver : public Presionable{
	int* etapa;
	bool* corriendo;
public:
	BotonVolver(Imagen* imagen, int* etapa, bool* corriendo);
	void presionar() override;
};

#endif //BOTON_VOLVER