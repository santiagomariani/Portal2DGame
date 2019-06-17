#ifndef CONTACTO_H
#define CONTACTO_H

#include "Box2D/Box2D.h"

class ContactListener : public b2ContactListener{
	// Se recibe un contacto. Podemos obtener los 2 fixtures que hicieron
	// contacto. Si un fixture tiene un dato, el mismo es un sensor, y tendra
	// como dato un objeto que hereda de Sensor. Si el dato lo tiene el body,
	// entonces el dato es un Cuerpo. Lo que se hace es fijarse si ambos tienen
	// datos y que es cada uno de los datos (Cuerpo o Sensor). Si ambos tienen
	// datos se envian mensajes para que luego cada objeto sepa que hacer ante
	// el contacto.
	void BeginContact(b2Contact* contact);
	// Lo mismo ocurre cuando termina el contacto, solo que ahora lo que tienen
	// que decidir los objetos, es que hacer cuando se termina el contacto.
	void EndContact(b2Contact* contact);
};

#endif //CONTACTO_H
