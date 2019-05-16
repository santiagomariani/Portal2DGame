#ifndef CHELL_H
#define CHELL_H
#include "Box2D/Box2D.h"
#include <SDL2/SDL.h>

class Chell{
	b2Body* cuerpo;
public:
	Chell(b2World& world, b2Vec2& pos);
	void moverDerecha();
	void moverIzquierda();
	void saltar();
	void mover(const Uint8 *state);
	b2Vec2 getPosition();

};

#endif //CHELL_H