#ifndef CONTACTO_DISPARO_H
#define CONTACTO_DISPARO_H
#include "Box2D/Box2D.h"

// Contact Listener entre Disparo y Roca (por ahora 1 tipo de Roca)
class ContactListenerDisparo : public b2ContactListener{
	void BeginContact(b2Contact* contact);
};

#endif //CONTACTO_DISPARO_H
