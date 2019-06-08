#include "boton.h"
#include <iostream>
#include "ids.h"
#include "config.h"

Boton::Boton(b2Vec2& pos, Mundo& mundo):
			Cuerpo(config::tam_base_boton_x*2,
				   config::tam_base_boton_y*2 + config::tam_sensor_boton_y*2 + 0.1){
	this->estado_actual = false;

	b2BodyDef base_def;
	base_def.type = b2_staticBody;
	base_def.position.Set(pos.x, pos.y);
	base = mundo.agregarBody(base_def);

	b2PolygonShape base_shape;
	b2FixtureDef base_fixture_def;
	base_fixture_def.shape = &base_shape;

	b2Vec2 centro(0,0);
	base_shape.SetAsBox(config::tam_base_boton_x, config::tam_base_boton_y);
	base->CreateFixture(&base_fixture_def);

	b2BodyDef boton_cuerpo_def;
	boton_cuerpo_def.type = b2_staticBody;
	boton_cuerpo_def.position.Set(pos.x, pos.y + config::tam_base_boton_y + config::tam_sensor_boton_y);
	cuerpo_boton = mundo.agregarBody(boton_cuerpo_def);

	b2PolygonShape cuerpo_shape;
	b2FixtureDef cuerpo_fixture_def;
	cuerpo_fixture_def.shape = &cuerpo_shape;

	cuerpo_shape.SetAsBox(config::tam_sensor_boton_x, config::tam_sensor_boton_y);
	cuerpo_boton->CreateFixture(&cuerpo_fixture_def);
	cuerpo_boton->SetUserData(this);
}

bool Boton::estaActivado(){
	return estado_actual;
}

void Boton::encender(){
	this->estado_actual = true;
}

void Boton::apagar(){
	this->estado_actual = false;
}

void Boton::empezarContacto(Cuerpo* otro){
	if (otro){
		this->encender();
	}
}

void Boton::terminarContacto(Cuerpo* otro){
	if (otro){
		this->apagar();
	}
}

uint8_t Boton::getId(){
	if (estado_actual){
		return ID_BOTON_PRENDIDO;
	}
	return ID_BOTON_APAGADO;
}

const b2Vec2& Boton::getPosition(){
	return base->GetPosition();
}

