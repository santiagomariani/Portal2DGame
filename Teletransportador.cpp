#include "Teletransportador.h"
#include <iostream>

Teletransportador::Teletransportador(b2Body* cuerpo,
									 b2Vec2& nueva_pos,
									 b2Vec2& velocidad, 
									 float32 angulo):
			cuerpo(cuerpo), nueva_pos(nueva_pos), 
			velocidad(velocidad), angulo(angulo){
}

void Teletransportador::activar(){
	cuerpo->SetTransform(nueva_pos, angulo);
	cuerpo->SetLinearVelocity(velocidad);
	//cuerpo->ApplyForceToCenter(velocidad, true);
	//cuerpo->ApplyLinearImpulseToCenter(velocidad, true);
}

