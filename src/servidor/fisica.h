#ifndef FISICA_H
#define FISICA_H

#include "mundo.h"
#include "personajes.h"
#include "Protocolo.h"
#include "cuerpo.h"
#include <vector>

class Fisica{
	Mundo& mundo;
	Personajes personajes;
public:
	explicit Fisica(Mundo& mundo);
	
	void agregarNuevaChell();
	
	void actualizar();
	
	std::vector<Cuerpo*> obtenerCuerpos();

    void agregarTeclado(int id, EstadoTeclado &teclado);

    void agregarMouse(int id, EstadoMouse &mouse);

    ~Fisica() = default;
};

#endif

