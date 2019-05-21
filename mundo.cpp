#include "mundo.h"
#include "roca.h"
#include "disparo.h"

Mundo::Mundo(const b2Vec2& gravedad) : mundo(gravedad){
}

void Mundo::setContactListener(b2ContactListener& listener){
	mundo.SetContactListener(&listener);
}

b2Body* Mundo::agregarBody(b2BodyDef& cuerpo_def){
	return mundo.CreateBody(&cuerpo_def);
}

void Mundo::destruirBody(b2Body* body){
	this->mundo.DestroyBody(body);
}

void Mundo::actualizar(){
	mundo.Step(1.0f / 60.0f, 6, 2);
}

b2Body* Mundo::obtenerBodies(){
	return this->mundo.GetBodyList();
}

