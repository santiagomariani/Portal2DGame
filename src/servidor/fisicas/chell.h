#ifndef CHELL_H
#define CHELL_H

#include "Box2D/Box2D.h"
#include "mundo.h"
#include "estado_teclado.h"
#include "cuerpo.h"
#include "pistola.h"
#include "roca.h"
#include "sensor_chell.h"
#include "estado_chell.h"
#include <SDL2/SDL.h>

// Representa al personaje Chell. 
// Puede disparar, agarrar una roca, moverse y saltar.
// Tiene una identidad (int) unica para diferenciar de otros personajes.

class Chell : public Cuerpo {
	int id;
	b2Body* cuerpo;
	Pistola pistola;
	Mundo& mundo;
	Roca* roca;
	b2Joint *joint_roca;
	std::unique_ptr<SensorChell> sensor;
	EstadoChell estado_chell;
public:
	Chell(int identidad, Mundo& mundo);
	// Se crea la Chell en la posicion recibida.
	void activar(b2Vec2& pos);
	Chell(Chell&& otro);
	// Se mueve la Chell en base al estado del teclado.
	void mover(EstadoTeclado& t);
	// La Chell actualiza su estado y muere.
	void morir();
	// Chell agarra una roca, si es posible y si recibe el input
	// necesario.
	void agarrarRoca(EstadoTeclado & t);
	// Devuelve el id asociado a la Chell.
	uint8_t getId() override;
	// Devuelve el id de la Chell (puede haber multiples Chells).
	int getIdPersonaje();
	// Crea un disparo para crear un portal azul.
	void dispararAzul(b2Vec2& pos_click);
	// Crea un disparo para crear un portal naranja.
	void dispararNaranja(b2Vec2& pos_click);
	// Devuelve la posicion de la Chell.
	const b2Vec2& getPosition();
	float getWidth();
	float getHeight();
	// Devuelve el b2Body asociado a la Chell.
	b2Body* getBody();
	// Devuelve el estado actual de la Chell.
	uint8_t obtenerEstado();
	// Devuelve la orientacion actual de la Chell.
	uint8_t obtenerOrientacion();
	// Destruye la roca que tiene la Chell(La roca resetea su posicion).
	void destruirRoca();
	void empezarContacto(Cuerpo* otro) override;
	void terminarContacto(Cuerpo* otro) override;
	void desactivar() override;
	void ganar();
};

#endif //CHELL_H
