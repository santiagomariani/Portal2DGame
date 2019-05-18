#include "mundo.h"
#include "roca.h"
#include "disparo.h"

Mundo::Mundo(const b2Vec2& gravedad) : mundo(gravedad){
}
void Mundo::agregarChell(int cliente){
	b2Vec2 pos(0, 0); // HARCODEO
	Chell* chell = new Chell(mundo, pos);
	personajes[cliente] = chell;
}
void Mundo::crearDisparo(int cliente, const b2Vec2& click){
	b2Vec2 pos_chell = personajes[cliente]->getPosition();
	Disparo d(mundo, pos_chell, click);
}
void Mundo::crearRoca(const b2Vec2& pos){
	Roca r(mundo, pos);
}
void Mundo::avanzar(){
	mundo.Step(1.0f / 60.0f, 6, 2); //HARCODEO PROFUNDO
}

const b2World& Mundo::getMundo(){
	return mundo;
}
