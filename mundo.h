#ifndef MUNDO_H
#define MUNDO_H

#include <map>
#include "Box2D/Box2D.h"
#include "chell.h"
#include "roca.h"
#include "disparo.h"
#include <vector>

class Mundo{
	b2World mundo;
	std::vector<Disparo> disparos;
	std::vector<Roca> rocas;
public:
	Mundo(const b2Vec2& gravedad);

	void crearDisparo(const b2Vec2& origen, const b2Vec2& destino);
	void crearRoca(const b2Vec2& pos);
	void avanzar();
	b2World& getMundo();

	std::vector<Disparo>& getDisparos();
	
};

#endif //MUNDO_H
