#ifndef PISTOLA_H
#define PISTOLA_H

#include "portal.h"
#include "disparo.h"

class Pistola{
	Mundo& mundo;
	Portal p_azul;
	Portal p_naranja;
	Disparo d_azul;
	Disparo d_naranja;
public:
	Pistola(Mundo& mundo);
    Pistola& operator=(Pistola&& otro);
    Pistola(Pistola&& otro);
	void dispararAzul(const b2Vec2& origen, const b2Vec2& destino);
	void dispararNaranja(const b2Vec2& origen, const b2Vec2& destino);
};

#endif 