#ifndef CHELL_H
#define CHELL_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "estado_teclado.h"
#include "cuerpo.h"
#include "pistola.h"
#include <SDL2/SDL.h>

class Chell : public Cuerpo {
	int id;
	b2Body* cuerpo;
	Pistola pistola;
public:
	Chell();
	Chell(int identidad);
	void activar(Mundo& mundo, b2Vec2& pos);
	Chell(Chell&& otro);
	Chell& operator=(Chell&& otro);
	void mover(EstadoTeclado& t);
	int getId();
	void dispararAzul(Mundo& mundo, b2Vec2& pos_click);
	void dispararNaranja(Mundo& mundo, b2Vec2& pos_click);
	const b2Vec2& getPosition();
	const b2Vec2& getVelocidad();
	void setVelocidad(b2Vec2& vel);
	void cambiarPosicion(const b2Vec2& pos);
	float getWidth();
	float getHeight();


	void empezarContacto(Cuerpo* otro) {}
};

#endif //CHELL_H
