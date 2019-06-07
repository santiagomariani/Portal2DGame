#ifndef BOTON_EDITAR_H
#define BOTON_EDITAR_H

#include "presionable.h"

class BotonEditar : public Presionable{
public:
	BotonEditar(Imagen* imagen);
	void presionar() override;
};

#endif //BOTON_EDITAR