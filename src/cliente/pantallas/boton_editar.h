#ifndef BOTON_EDITAR_H
#define BOTON_EDITAR_H

#include "presionable.h"

class BotonEditar : public Presionable{
	int* etapa;
	bool* corriendo;
public:
	BotonEditar(Imagen* imagen, int* etapa, bool* corriendo);

	// Ejecuta el modo edicion de mapas
	void presionar() override;
};

#endif //BOTON_EDITAR