#include "disparo.h"
#include "Box2D/Box2D.h"
#define RADIO_RAYO 0.3f
#define DENSIDAD_RAYO 1
#define CTE_VELOCIDAD_RAYO 3

Disparo::Disparo(b2World& world, b2Vec2& origen, b2Vec2& destino){
	b2BodyDef circle_body_def;
	circle_body_def.type = b2_dynamicBody;
	circle_body_def.position.Set(origen.x, origen.y);
	circle_body = world.CreateBody(&circle_body_def);

	b2CircleShape circleShape;
	circleShape.m_p.Set(origen.x, origen.y);
	circleShape.m_radius = RADIO_RAYO;
	b2FixtureDef circle_fixture_def;
	circle_fixture_def.shape = &circleShape;
	circle_fixture_def.density = DENSIDAD_RAYO;
	circle_body->CreateFixture(&circle_fixture_def);

	b2Vec2 vel = destino;
	vel -= origen;
	vel.Normalize();
	vel *= CTE_VELOCIDAD_RAYO;
	circle_body->SetGravityScale(0);
	circle_body->SetLinearVelocity(vel);
	circle_body->SetUserData(this);
}

b2Vec2 Disparo::getPosition(){
	return circle_body->GetPosition();
}
float32 Disparo::getAngle(){
	return circle_body->GetAngle();
}





