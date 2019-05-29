#include <iostream>
#include "disparo.h"
#include "BloqueRoca.h"
#include "contact_listener.h"

#define ID_ROCA 1
#define ID_DISPARO 2


void ContactListener::BeginContact(b2Contact* contact){
	b2Fixture* fixture_A = contact->GetFixtureA();
	b2Fixture* fixture_B = contact->GetFixtureB();

	Cuerpo* entity_A = (Cuerpo*)(fixture_A->GetBody()->GetUserData());
	Cuerpo* entity_B = (Cuerpo*)(fixture_B->GetBody()->GetUserData());
	
	if (!entity_A || !entity_B){
		return;
	}

	entity_A->empezarContacto(entity_B);
	entity_B->empezarContacto(entity_A);
}

void ContactListener::EndContact(b2Contact* contact){
	b2Fixture* fixture_A = contact->GetFixtureA();
	b2Fixture* fixture_B = contact->GetFixtureB();

	Cuerpo* entity_A = (Cuerpo*)(fixture_A->GetBody()->GetUserData());
	Cuerpo* entity_B = (Cuerpo*)(fixture_B->GetBody()->GetUserData());
	
	if (!entity_A || !entity_B){
		return;
	}

	entity_A->terminarContacto(entity_B);
	entity_B->terminarContacto(entity_A);
}
