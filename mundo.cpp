#include "mundo.h"
#include "roca.h"
#include "disparo.h"

Mundo::Mundo(const b2Vec2& gravedad) : mundo(gravedad){
}
void Mundo::crearDisparo(const b2Vec2& origen, const b2Vec2& destino){
	Disparo d(mundo, origen, destino);
	disparos.push_back(std::move(d));
}
void Mundo::crearRoca(const b2Vec2& pos){
	Roca r(mundo, pos);
	rocas.push_back(std::move(r));
}
void Mundo::avanzar(){
	mundo.Step(1.0f / 60.0f, 6, 2); //HARCODEO PROFUNDO
}
b2World& Mundo::getMundo(){
	return mundo;
}
