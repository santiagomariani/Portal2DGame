#ifndef PERSONAJES_H
#define PERSONAJES_H
#include <map>
#include <estado_mouse.h>
#include "chell.h"
#include "Box2D/Box2D.h"
#include "mundo.h"

class Personajes{
	std::map<int,Chell> personajes;
	std::map<int, EstadoTeclado> teclados;
	int siguiente_client;
	Mundo& mundo;
public:
	explicit Personajes(Mundo& m);

	// Devuelve el id de la chell
	int agregar_chell();

	Chell& obtener_chell(int chell_id);
	

    void actualizarChells();

    void moverChell(int chell_id, EstadoTeclado &teclado);

    void agregarClick(int chell_id, EstadoMouse &mouse);

    void agregarTeclado(int id, EstadoTeclado teclado);

    ~Personajes() = default;
};



#endif

