#include "boton.h"
#include <iostream>
#include "ids.h"
#define TAM_BOTON_X 0.25
#define TAM_BOTON_Y 0.025//0.0312
#define TAMANIO_BASE_X 0.5
#define TAMANIO_BASE_Y 0.1//0.15

Boton::Boton(bool abrir_puerta_al_encender, b2Vec2& pos, Mundo& mundo):
			Cuerpo(TAMANIO_BASE_X*2,
				   TAMANIO_BASE_Y*2 + TAM_BOTON_Y*2 + 0.1){
	this->activacion_compuerta = abrir_puerta_al_encender;
	this->estado_actual = false;

	b2BodyDef base_def;
	base_def.type = b2_staticBody;
	base_def.position.Set(pos.x, pos.y);
	base = mundo.agregarBody(base_def);

	b2PolygonShape base_shape;
	b2FixtureDef base_fixture_def;
	base_fixture_def.shape = &base_shape;

	b2Vec2 centro(0,0);
	base_shape.SetAsBox(TAMANIO_BASE_X, TAMANIO_BASE_Y);
	base->CreateFixture(&base_fixture_def);

	b2BodyDef boton_cuerpo_def;
	boton_cuerpo_def.type = b2_staticBody;
	boton_cuerpo_def.position.Set(pos.x, pos.y + TAMANIO_BASE_Y + TAM_BOTON_Y);
	cuerpo_boton = mundo.agregarBody(boton_cuerpo_def);

	b2PolygonShape cuerpo_shape;
	b2FixtureDef cuerpo_fixture_def;
	cuerpo_fixture_def.shape = &cuerpo_shape;

	cuerpo_shape.SetAsBox(TAM_BOTON_X, TAM_BOTON_Y);
	cuerpo_boton->CreateFixture(&cuerpo_fixture_def);
	cuerpo_boton->SetUserData(this);
}

bool Boton::activoParaCompuerta(){
	return estado_actual == activacion_compuerta;
}

void Boton::encender(){
	std::cout << "se encendio\n";
	this->estado_actual = true;
}

void Boton::apagar(){
	std::cout << "se apago\n";
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

int Boton::getId(){
	return ID_BOTON_APAGADO;
}

const b2Vec2& Boton::getPosition(){
	return base->GetPosition();
}

