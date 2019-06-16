#ifndef ESTADO_COMPUERTA_H
#define ESTADO_COMPUERTA_H

#include "ids.h"
#include "cuerpo.h"

// Representa los distintos estados de la compuerta:
// abierta, abriendo, cerrada, cerrando

class EstadoCompuerta{
public:
	// Actualiza el estado, devolviendo el estado siguiente
	// que corresponda
	virtual EstadoCompuerta* actualizar(bool activa, b2Body* puerta) = 0;
	virtual void empezarContacto(Cuerpo* cuerpo) = 0;
	virtual int getId() = 0;
	virtual ~EstadoCompuerta() = default;
};

#endif
