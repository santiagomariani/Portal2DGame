#ifndef ESTADO_CERRANDO_H
#define ESTADO_CERRANDO_H 
#include "estado_compuerta.h"

class EstadoCerrando : public EstadoCompuerta{
public:
	EstadoCerrando();
	EstadoCompuerta* actualizar(bool activa);
	void empezarContacto(Cuerpo* cuerpo);
	~EstadoCerrando();
};

#endif

