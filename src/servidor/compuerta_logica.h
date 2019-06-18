#ifndef COMPUERTA_LOGICA_H
#define COMPUERTA_LOGICA_H

#include <memory>

// Representa una compuerta logica
// (como en un circuito)

class CompuertaLogica {
public:
	virtual bool encendida() = 0;
	virtual void agregar(std::shared_ptr<CompuertaLogica> compuerta) = 0;

};

#endif
