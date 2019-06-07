#ifndef BOTON_JUGAR_H
#define BOTON_JUGAR_H

#include "presionable.h"

class BotonJugar : public Presionable{
public:
	BotonJugar(Imagen* imagen);
	void presionar() override;
};

#endif //BOTON_JUGAR