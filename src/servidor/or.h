#ifndef OR_H
#define OR_H

#include <vector>
#include "compuerta_logica.h"
#include "boton.h"

// Compuerta logia Or

class Or : public CompuertaLogica {
	std::vector<std::shared_ptr<CompuertaLogica>> compuertas;
public:
	Or();
	void agregar(std::shared_ptr<CompuertaLogica> compuerta);
	bool encendida();
	~Or() = default;
};

#endif
