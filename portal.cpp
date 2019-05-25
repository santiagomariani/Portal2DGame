#include "portal.h"
#include "chell.h"
#include <math.h>
#include "Box2D/Box2D.h"
#define TAMANIO_PORTAL_X 0.5
#define TAMANIO_PORTAL_Y 0.05


#define PI 3.14159265


Portal::Portal(Mundo& mundo, const b2Vec2& pos, const b2Vec2& normal){
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_staticBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo = mundo.agregarBody(cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	polygonShape.SetAsBox(TAMANIO_PORTAL_X, TAMANIO_PORTAL_Y);
	cuerpo->CreateFixture(&myFixtureDef);

	orientacion = atan2(normal.y, normal.x);
	if (orientacion < 0){
		orientacion += 2 * PI;
	}

}
float Portal::getAnguloSalida(){
	return orientacion;
}
float Portal::getAnguloEntrada(){
	if (orientacion - PI < 0){
		return orientacion + PI;
	}
	return orientacion - PI;
}
void Portal::expulsar(Chell* chell, float orientacion_otro){
	float nuevo_ang = getAnguloSalida() - orientacion_otro;
	b2Rot rotador(nuevo_ang);
	b2Vec2 vel = chell->getVelocidad();
	b2Vec2 nueva_vel = b2Mul(rotador, vel);
	chell->setVelocidad(nueva_vel);
	chell->cambiarPosicion(cuerpo->GetPosition());
}
void Portal::teletransportar(Chell* chell){
	hermano->expulsar(chell, getAnguloEntrada());
}

