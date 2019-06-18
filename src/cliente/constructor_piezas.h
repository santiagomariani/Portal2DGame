#ifndef CONTRUCTOR_PIEZAS_H
#define CONTRUCTOR_PIEZAS_H

#include "pieza.h"
#include "imagen.h"
#include <map>

class ConstructorDePiezas{
	std::map<int, Imagen*>& imagenes;
	int identificador = 0;
public:
	ConstructorDePiezas(std::map<int, Imagen*>& imagenes);

	//Crea las piezas
	Pieza construir(int id);
};

#endif //CONTRUCTOR_PIEZAS
