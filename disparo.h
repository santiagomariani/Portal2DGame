#ifndef DISPARO_H
#define DISPARO_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "cuerpo.h"

class Disparo : public Cuerpo{
	b2Body* cuerpo;
	bool listo;
public:
	Disparo();
	void activar(Mundo& mundo, const b2Vec2& origen, const b2Vec2& destino);
	Disparo(Disparo&& otro);
	bool terminado();
	void terminar();
	void remover();
	Disparo& operator=(Disparo& otro);
	Disparo& operator=(Disparo&& otro);
	const b2Vec2& getPosition();
	double getAngle();
	int getId();
};

#endif //DISPARO_H
