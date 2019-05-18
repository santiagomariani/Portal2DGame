#ifndef MUNDO_H
#define MUNDO_H

#include <map>
#include "Box2D/Box2D.h"
#include "chell.h"

class Mundo{
	b2World mundo;
	std::map<int, Chell*> personajes;
public:
	Mundo(const b2Vec2& gravedad);

	void agregarChell(int cliente);
	void crearDisparo(int cliente, const b2Vec2& click);
	void crearRoca(const b2Vec2& pos);
	void avanzar();




	const b2World& getMundo();


	
};

#endif //MUNDO_H
