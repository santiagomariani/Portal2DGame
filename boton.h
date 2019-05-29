#ifndef BOTON_H
#define BOTON_H 

#include "Box2D/Box2D.h"
#include "cuerpo.h"
#include "mundo.h"

class Boton : public Cuerpo{
	bool estado_actual; // true si presionado/encendido, false si no
	b2Body* base;
	b2Body* cuerpo_boton;
public:
	Boton(b2Vec2& pos, Mundo& mundo);

	// Devuelve si esta encendido o no
	bool encendido() override;

	// Enciende boton
	void encender();

	// Apaga el boton
	void apagar();

	void empezarContacto(Cuerpo* otro);
	void terminarContacto(Cuerpo* otro) override;
	const b2Vec2& getPosition();
	int getId();
	~Boton() = default;
};



#endif
