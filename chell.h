#ifndef CHELL_H
#define CHELL_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "estado_teclado.h"
#include <SDL2/SDL.h>

class Chell{
	b2Body* cuerpo;
public:
	Chell();
	Chell(Mundo& mundo, b2Vec2& pos);
	Chell(Chell&& otro);
	Chell& operator=(Chell&& otro);
	void mover(EstadoTeclado& t);
	int getId();

	void moverDerecha();
	void moverIzquierda();
	void saltar();
	b2Vec2 getPosition(); //Copia??

};

#endif //CHELL_H
