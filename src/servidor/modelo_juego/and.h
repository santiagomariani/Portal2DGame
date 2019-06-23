#ifndef AND_H
#define AND_H

#include <vector>
#include "compuerta_logica.h"
#include "boton.h"

// Representa la compuerta And para conectar una o varias compuertas logicas
class And : public CompuertaLogica {
	std::vector<std::shared_ptr<CompuertaLogica>> compuertas;
public:
	And();

	// Agrega una compuerta logica a la entrada de la And.
	void agregar(std::shared_ptr<CompuertaLogica> compuerta);

	// Devuelve el resultado actual de hacer And con las compuertas.
	// true si esta encendida (1) o false si no (0)
	bool encendida();
	~And();
};

#endif

