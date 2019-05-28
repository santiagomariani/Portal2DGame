#ifndef TELETRANSPORTADOR_H
#define TELETRANSPORTADOR_H

#include "Box2D/Box2D.h"


class Teletransportador{
	b2Body* cuerpo;
	b2Vec2 nueva_pos;
	b2Vec2 velocidad;
	float angulo;
public:
	Teletransportador(b2Body* cuerpo, b2Vec2& nueva_pos, 
					  b2Vec2& velocidad, float32 angulo = 0.0f);
	void activar();
	~Teletransportador() = default;
};

#endif
