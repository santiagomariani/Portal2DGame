#ifndef ESTADO_ABIERTA_H
#define ESTADO_ABIERTA_H
#include "estado_compuerta.h"

class EstadoAbierta : public EstadoCompuerta{
public:
	EstadoAbierta();
	EstadoCompuerta* actualizar(bool activa, b2Body* puerta);
	void empezarContacto(Cuerpo* cuerpo);
	int getId();
	~EstadoAbierta() override = default;
};

#endif

