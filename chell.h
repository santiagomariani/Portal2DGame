#ifndef CHELL_H
#define CHELL_H
#include "Box2D/Box2D.h"
#include "estado_teclado.h"
#include <SDL2/SDL.h>

class Chell{
	b2Body* cuerpo;
public:
	Chell(b2World& world, b2Vec2& pos);
	Chell(Chell&& otro);
	void moverDerecha();
	void moverIzquierda();
	void saltar();
	void mover(EstadoTeclado& t);
	b2Vec2 getPosition(); //Copia??

};

#endif //CHELL_H
