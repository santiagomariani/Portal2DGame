#ifndef FISICA_H
#define FISICA_H

#include "mundo.h"
#include "personajes.h"
#include "Protocolo.h"

class Fisica{
	Mundo& mundo;
	Personajes personajes;
	Protocolo& protocolo;
public:
	Fisica(Protocolo& protocolo, Mundo& mundo);
	void actualizar();
	void enviarCuerpos();
	~Fisica() = default;
};

#endif

