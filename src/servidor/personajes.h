#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <map>
#include <estado_mouse.h>
#include "chell.h"
#include "Box2D/Box2D.h"
#include "mundo.h"

// Clase que maneja las personajes (Chells)
// y los actualiza segun su id del respectivo jugador (cliente).

class Personajes{
	std::map<int,Chell> personajes;
	std::map<int, EstadoTeclado> teclados;
	std::vector<b2Vec2>& pos_chells;
	int siguiente_client;
	Mundo& mundo;

    void moverChell(int chell_id, EstadoTeclado &teclado);

public:
    Personajes(Mundo& m, std::vector<b2Vec2>& pos_chells);

	// Devuelve el id de la Chell creada.
	int agregar_chell(b2Vec2& pos);
	Chell& obtener_chell(int chell_id);
	// Actualiza el movimiento de cada Chell
	// segun lo recibido del teclado y mouse.
    void actualizarChells();
    // Agrega un click de un jugador.
    void agregarClick(int chell_id, EstadoMouse &mouse);
    // Actualiza el teclado de un jugador.
    void agregarTeclado(int id, EstadoTeclado teclado);
    void eliminarChell(int id);
    // Devuelve la cantidad de Chells que existen en el mundo
    // en esa iteracion.
    int cantChells();
    ~Personajes() = default;
};



#endif

