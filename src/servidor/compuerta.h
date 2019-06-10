#ifndef COMPUERTA_H
#define COMPUERTA_H

#include "Box2D/Box2D.h"
#include "mundo.h"
#include "compuerta_logica.h"
#include "cuerpo.h"
#include "estado_compuerta.h"

class Compuerta : public Cuerpo{
	CompuertaLogica& compuerta_logica;
	b2Body* cuerpo;
	b2Body* base;
	EstadoCompuerta* estado;
public:
	Compuerta(b2Vec2& pos, Mundo& mundo, CompuertaLogica& compuerta_logica);
	bool estaActiva();
	void actualizar() override;
	uint8_t getId();
	const b2Vec2& getPosition();
	void empezarContacto(Cuerpo* otro);
	~Compuerta() = default;
};

#endif
