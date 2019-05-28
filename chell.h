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
	Mundo& mundo;
public:
	Chell(int identidad, Mundo& mundo);
	void activar(b2Vec2& pos);
	Chell(Chell&& otro);
	void mover(EstadoTeclado& t);
	int getId();
	void dispararAzul(b2Vec2& pos_click);
	void dispararNaranja(b2Vec2& pos_click);
	const b2Vec2& getPosition();
	float getWidth();
	float getHeight();
	b2Body* getBody();


	void empezarContacto(Cuerpo* otro);
};

#endif //CHELL_H
