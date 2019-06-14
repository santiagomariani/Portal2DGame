#ifndef AND_H
#define AND_H

#include <vector>
#include "compuerta_logica.h"
#include "boton.h"

class And : public CompuertaLogica {
	std::vector<std::shared_ptr<CompuertaLogica>> compuertas;
public:
	And();
	void agregar(std::shared_ptr<CompuertaLogica>& compuerta);

	bool encendida();
	~And();
};

#endif

