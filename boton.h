#ifndef BOTON_H
#define BOTON_H 

#include "Box2D/Box2D.h"
#include "cuerpo.h"
#include "mundo.h"

class Boton : public Cuerpo{
	bool activacion_compuerta; // true si activa compuerta cuando
							  // esta presionado/encendido
							  // false activa compuerta cuando esta apagado
	bool estado_actual; // true si presionado/encendido, false si no
	b2Body* base;
	b2Body* cuerpo_boton;
public:
	Boton(bool abrir_puerta_al_encender, b2Vec2& pos, Mundo& mundo);

	// Devuelve true si en su estado puede activar la compuerta
	bool activoParaCompuerta();

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
