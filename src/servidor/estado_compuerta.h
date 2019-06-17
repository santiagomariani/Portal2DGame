#ifndef ESTADO_COMPUERTA_H
#define ESTADO_COMPUERTA_H

#include "ids.h"
#include "cuerpo.h"

class EstadoCompuerta{
public:
	virtual EstadoCompuerta* actualizar(bool activa, b2Body* puerta) = 0;
	virtual void empezarContacto(Cuerpo* cuerpo) = 0;
	virtual int getId() = 0;
	virtual ~EstadoCompuerta() = default;
};

#endif
