#include "roca.h"
#include "Box2D/Box2D.h"
#define TAMANIO_BLOQUE_X 0.5
#define TAMANIO_BLOQUE_Y 0.5

Roca::Roca(b2World& world, const b2Vec2& pos){
	b2BodyDef cuerpo_def;
	cuerpo_def.type = b2_staticBody;
	cuerpo_def.position.Set(pos.x, pos.y);
	cuerpo = world.CreateBody(&cuerpo_def);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	/*b2Vec2 vs[4];
	vs[0].Set(0.0f, 1.0f);
	vs[1].Set(-1.0f, 0.0f);
	vs[2].Set(0.0f, -1.0f);
	vs[3].Set(1.0f, 0.0f);
	b2ChainShape chain;
	chain.CreateLoop(vs, 4);

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &chain;
	myFixtureDef.density = 1;*/

	polygonShape.SetAsBox(TAMANIO_BLOQUE_X, TAMANIO_BLOQUE_Y);
	cuerpo->CreateFixture(&myFixtureDef);
	cuerpo->SetUserData(this);
}

b2Vec2 Roca::getPosition(){
	return cuerpo->GetPosition();
}

