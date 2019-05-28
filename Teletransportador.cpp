#include "Teletransportador.h"
#include <iostream>

Teletransportador::Teletransportador(b2Body* cuerpo,
									 b2Vec2& nueva_pos,
									 b2Vec2& velocidad, 
									 float32 angulo):
			cuerpo(cuerpo), nueva_pos(nueva_pos), 
			velocidad(velocidad), angulo(angulo){
	std::cout << "creacion telep, nueva pos: " << nueva_pos.x << " " << nueva_pos.y << std::endl;
}

void Teletransportador::activar(){
	
	std::cout << "teletransport a: " << nueva_pos.x << " " << nueva_pos.y << std::endl;
	cuerpo->SetTransform(nueva_pos, angulo);
	cuerpo->SetLinearVelocity(velocidad); // abajo o arriba?
	
}

