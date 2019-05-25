#ifndef PISTOLA_H
#define PISTOLA_H

#include "portal.h"
#include "disparo.h"

class Pistola{
	Portal p_azul;
	Portal p_naranja;
	Disparo d_azul;
	Disparo d_naranja;
public:
	Pistola();
	void dispararAzul(Mundo& mundo, const b2Vec2& origen, const b2Vec2& destino);
	void dispararNaranja(Mundo& mundo, const b2Vec2& origen, const b2Vec2& destino);
};

#endif 