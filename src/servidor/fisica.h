#ifndef FISICA_H
#define FISICA_H

#include "mundo.h"
#include "personajes.h"
#include "Protocolo.h"
#include "cuerpo.h"
#include <vector>

class Fisica{
	Mundo& mundo;
	Personajes personajes;
public:
	Fisica(Mundo& mundo);
	void actualizar();
	void actualizarChell(int id, EstadoTeclado& teclado, EstadoMouse& mouse);
	std::vector<Cuerpo*> obtenerCuerpos();
	~Fisica() = default;
};

#endif

