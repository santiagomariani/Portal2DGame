#ifndef ESTADO_LOGICO_H
#define ESTADO_LOGICO_H

#include "compuerta_logica.h"
#include "cuerpo.h"

// Encapsula un cuerpo en una compuerta logica
// y así poder agregarlo a diferentes compuertas And, Or, etc.

class EstadoLogico : public CompuertaLogica {
	Cuerpo& cuerpo;
public:
	EstadoLogico(Cuerpo& cuerpo);
	bool encendida();
	~EstadoLogico() = default;
};

#endif
