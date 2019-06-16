#ifndef COMPUERTA_H
#define COMPUERTA_H

#include "Box2D/Box2D.h"
#include "mundo.h"
#include "compuerta_logica.h"
#include "cuerpo.h"
#include "estado_compuerta.h"

// Compuerta del juego

class Compuerta : public Cuerpo{
	CompuertaLogica& compuerta_logica;
	b2Body* cuerpo;
	b2Body* base;
	EstadoCompuerta* estado;
public:
	// Recibe una compuerta logica de la cual se obtiene el estado booleando
	// para que se abra o no la compuerta.
	Compuerta(b2Vec2& pos, Mundo& mundo, CompuertaLogica& compuerta_logica);
	// Devuelve si la compuerta esta activa o no
	// (abierta o no)
	bool estaActiva();
	// Actualiza el estado de la compuerta (abierta o cerrada)
	void actualizar() override;
	uint8_t getId();
	const b2Vec2& getPosition();
	void empezarContacto(Cuerpo* otro);
	~Compuerta();
};

#endif
