#ifndef ESTADO_COMPUERTA_H
#define ESTADO_COMPUERTA_H
#include "cuerpo.h"

class EstadoCompuerta{
public:
	virtual EstadoCompuerta* actualizar(bool activa) = 0;
	virtual void empezarContacto(Cuerpo* cuerpo) = 0;
};

#endif
