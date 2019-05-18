#ifndef PERSONAJES_H
#define PERSONAJES_H
#include <map>
#include "chell.h"
#include "Box2D/Box2D.h"
#include "mundo.h"

class Personajes{
	std::map<int,Chell> personajes;
	int siguiente_client;
	Mundo& mundo;
public:
	explicit Personajes(Mundo& m);

	// Devuelve el id de la chell
	int agregar_chell();

	Chell& obtener_chell(int chell_id);

	//void disparar(int chell_id, b2Vec2& click_pos);

	//void mover_chell(int chell_id, EstadoTeclado& teclado);

	//std::map<int, Chell>& getPersonajes();

	~Personajes() = default;
};



#endif

