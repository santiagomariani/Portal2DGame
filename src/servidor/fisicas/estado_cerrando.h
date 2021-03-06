#ifndef ESTADO_CERRANDO_H
#define ESTADO_CERRANDO_H 
#include "estado_compuerta.h"

class EstadoCerrando : public EstadoCompuerta{
public:
	EstadoCerrando();
	EstadoCompuerta* actualizar(bool activa, b2Body* puerta);
	void empezarContacto(Cuerpo* cuerpo);
	int getId();
	~EstadoCerrando() override = default;
};

#endif

