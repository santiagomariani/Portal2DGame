#ifndef COMPUERTA_H
#define COMPUERTA_H

#include "Box2D/Box2D.h"
#include "mundo.h"
#include "compuerta_logica.h"
#include "cuerpo.h"

class Compuerta : public Cuerpo{
	//std::vector<CompuertaLogica>& compuertas;
	CompuertaLogica& compuerta_logica;
	b2Body* cuerpo;
	b2Body* base;
public:
	Compuerta(b2Vec2& pos, Mundo& mundo, CompuertaLogica& compuerta_logica);
	bool estaActiva();
	void actualizar();
	int getId();
	const b2Vec2& getPosition();
	void empezarContacto(Cuerpo* otro);
	~Compuerta() = default;
};

#endif
