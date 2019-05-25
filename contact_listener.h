#ifndef CONTACTO_H
#define CONTACTO_H
#include "Box2D/Box2D.h"

class ContactListener : public b2ContactListener{
	void BeginContact(b2Contact* contact);
};

#endif //CONTACTO_H
