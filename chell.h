#ifndef CHELL_H
#define CHELL_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "estado_teclado.h"
#include "cuerpo.h"
#include "disparo.h"
#include <SDL2/SDL.h>

class Chell : public Cuerpo{
	b2Body* cuerpo;
	Disparo disparo;
public:
	Chell();
	Chell(Mundo& mundo, b2Vec2& pos);
	Chell(Chell&& otro);
	Chell& operator=(Chell&& otro);
	void mover(EstadoTeclado& t);
	int getId();

	void disparar(Mundo& mundo, b2Vec2& pos_click);
	void moverDerecha();
	void moverIzquierda();
	void saltar();
	const b2Vec2& getPosition();

};

#endif //CHELL_H
