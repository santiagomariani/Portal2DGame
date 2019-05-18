#include "mundo.h"
#include "roca.h"
#include "disparo.h"

Mundo::Mundo(const b2Vec2& gravedad) : mundo(gravedad){
}
b2Body* Mundo::agregarBody(b2BodyDef& cuerpo_def){
	return mundo.CreateBody(&cuerpo_def);
}
void Mundo::actualizar(){
	mundo.Step(1.0f / 60.0f, 6, 2);
}