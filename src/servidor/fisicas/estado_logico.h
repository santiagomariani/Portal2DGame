#ifndef ESTADO_LOGICO_H
#define ESTADO_LOGICO_H

#include "compuerta_logica.h"
#include "cuerpo.h"

// Encapsula un cuerpo en una compuerta logica
// y así poder agregarlo a diferentes compuertas And, Or, etc.

class EstadoLogico : public CompuertaLogica {
	std::unique_ptr<Cuerpo> cuerpo;
public:
	EstadoLogico(std::unique_ptr<Cuerpo> cuerpo);
	bool encendida();
	void agregar(std::shared_ptr<CompuertaLogica> compuerta) override;
	~EstadoLogico() = default;
};

#endif
