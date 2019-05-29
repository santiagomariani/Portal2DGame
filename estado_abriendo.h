#ifndef ESTADO_ABRIENDO_H
#define ESTADO_ABRIENDO_H
#include "estado_compuerta.h"

class EstadoAbriendo : public EstadoCompuerta{
public:
	EstadoAbriendo();
	EstadoCompuerta* actualizar(bool activa);
	void empezarContacto(Cuerpo* cuerpo);
	~EstadoAbriendo();
};

#endif

