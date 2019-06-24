#ifndef ESTADO_CERRADA_H
#define ESTADO_CERRADA_H
#include "estado_compuerta.h"

class EstadoCerrada : public EstadoCompuerta{
public:
	EstadoCerrada();
	EstadoCompuerta* actualizar(bool activa, b2Body* puerta);
	void empezarContacto(Cuerpo* cuerpo);
	int getId();
	~EstadoCerrada() override = default;
};

#endif

