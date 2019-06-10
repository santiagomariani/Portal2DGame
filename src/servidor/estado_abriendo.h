#ifndef ESTADO_ABRIENDO_H
#define ESTADO_ABRIENDO_H
#include "estado_compuerta.h"

class EstadoAbriendo : public EstadoCompuerta{
public:
	EstadoAbriendo();
	EstadoCompuerta* actualizar(bool activa, b2Body* puerta);
	void empezarContacto(Cuerpo* cuerpo);
	int getId();
	~EstadoAbriendo();
};

#endif

