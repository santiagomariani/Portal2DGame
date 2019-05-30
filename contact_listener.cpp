#include <iostream>
#include "disparo.h"
#include "BloqueRoca.h"
#include "contact_listener.h"

#define ID_BLOQUE_ROCA 1
#define ID_DISPARO 2

Cuerpo* obtenerCuerpo(b2Fixture* fixture){
	if (fixture->GetUserData()){
		return (Cuerpo*)(fixture->GetUserData());
	} else {
		return (Cuerpo*)(fixture->GetBody()->GetUserData());
	}
}


void ContactListener::BeginContact(b2Contact* contact){
	b2Fixture* fixture_A = contact->GetFixtureA();
	b2Fixture* fixture_B = contact->GetFixtureB();

	Cuerpo* entity_A = obtenerCuerpo(fixture_A);
	Cuerpo* entity_B = obtenerCuerpo(fixture_B);

	if (!entity_A || !entity_B){
		return;
	}

	entity_A->empezarContacto(entity_B);
	entity_B->empezarContacto(entity_A);
}

void ContactListener::EndContact(b2Contact* contact){
	b2Fixture* fixture_A = contact->GetFixtureA();
	b2Fixture* fixture_B = contact->GetFixtureB();

	Cuerpo* entity_A = obtenerCuerpo(fixture_A);
	Cuerpo* entity_B = obtenerCuerpo(fixture_B);

	if (!entity_A || !entity_B){
		return;
	}

	entity_A->terminarContacto(entity_B);
	entity_B->terminarContacto(entity_A);
}
