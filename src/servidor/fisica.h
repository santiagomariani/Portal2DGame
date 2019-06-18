#ifndef FISICA_H
#define FISICA_H

#include "mundo.h"
#include "personajes.h"
#include "protocolo.h"
#include "cuerpo.h"
#include <vector>

// Encapsula al mundo y maneja los comportamientos de los personajes
// segun el input de cada cliente

class Fisica{
	Mundo& mundo;
	Personajes personajes;
    std::vector<b2Vec2> pos_chells;
public:
	explicit Fisica(Mundo& mundo);
	// Agrega un spawn point para los personajes
	void agregarPosChell(b2Vec2& pos_chell);
	// Agrega una Chell al mundo
	void agregarNuevaChell();
	// Actualiza todo lo relacionado al mundo
	void actualizar();
	// Devuelve el vector de Cuerpos que pertenecen al mundo
	// en la actual iteracion.
	std::vector<Cuerpo*> obtenerCuerpos();
	// Agrega un teclado para una determinada Chell
    void agregarTeclado(int id, EstadoTeclado &teclado);
    // Agrega un click para una determinada Chell
    void agregarMouse(int id, EstadoMouse &mouse);
    void eliminarChell(int id_chell);
    // Devuelve la cantidad de personajes que hay en la actual iteracion
    int cantChells();
    ~Fisica() = default;
};

#endif

