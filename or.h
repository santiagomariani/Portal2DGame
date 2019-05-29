#ifndef OR_H
#define OR_H

#include <vector>
#include "compuerta_logica.h"
#include "boton.h"

class Or : public CompuertaLogica {
	std::vector<CompuertaLogica>& compuertas;
	//std::vector<Receptor>& receptores;
public:
	Or(std::vector<CompuertaLogica>& compuertas);
	//Or(std::vector<Boton>& receptores);

	bool encendida();
	~Or() = default;
};

#endif
