#ifndef OR_H
#define OR_H

#include <vector>
#include "compuerta_logica.h"
#include "boton.h"

class Or : public CompuertaLogica {
	//std::unique_ptr<std::vector<CompuertaLogica>> compuertas;
	std::vector<CompuertaLogica*> compuertas;
	//std::vector<Receptor>& receptores;
public:
	Or();
	//Or(std::vector<Boton>& receptores);
	void agregar(CompuertaLogica* compuerta);
	bool encendida();
	~Or() = default;
};

#endif
