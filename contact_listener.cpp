#include <iostream>
#include "disparo.h"
#include "BloqueRoca.h"
#include "contact_listener.h"

#define ID_ROCA 1
#define ID_DISPARO 2

/*bool getDisparoYRoca(b2Contact* contact, Disparo*& disp, BloqueRoca*& roca){
	b2Fixture* fixture_A = contact->GetFixtureA();
	b2Fixture* fixture_B = contact->GetFixtureB();
  
	bool sensor_A = fixture_A->IsSensor();
	bool sensor_B = fixture_B->IsSensor();
	if (!(sensor_A ^ sensor_B)){
		return false;
	}
	Cuerpo* entity_A = (Cuerpo*)(fixture_A->GetBody()->GetUserData());
	Cuerpo* entity_B = (Cuerpo*)(fixture_B->GetBody()->GetUserData());
	int id_A = entity_A->getId();
	int id_B = entity_B->getId();

	if (id_A == ID_DISPARO && id_B == ID_ROCA){
		disp = static_cast<Disparo*>(entity_A);
		roca = static_cast<BloqueRoca*>(entity_B);
		return true;
	}
	if (id_B == ID_DISPARO && id_A == ID_ROCA){
		disp = static_cast<Disparo*>(entity_B);
		roca = static_cast<BloqueRoca*>(entity_A);
		return true;
	}
	return false;
}

*/

void ContactListener::BeginContact(b2Contact* contact){
	b2Fixture* fixture_A = contact->GetFixtureA();
	b2Fixture* fixture_B = contact->GetFixtureB();

	Cuerpo* entity_A = (Cuerpo*)(fixture_A->GetBody()->GetUserData());
	Cuerpo* entity_B = (Cuerpo*)(fixture_B->GetBody()->GetUserData());

	entity_A->empezarContacto(entity_B);
	entity_B->empezarContacto(entity_A);
}
