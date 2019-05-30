#ifndef ESTADO_ABIERTA_H
#define ESTADO_ABIERTA_H
#include "estado_compuerta.h"

class EstadoAbierta : public EstadoCompuerta{
public:
	EstadoAbierta();
	EstadoCompuerta* actualizar(bool activa);
	void empezarContacto(Cuerpo* cuerpo);
	~EstadoAbierta();
};

#endif

