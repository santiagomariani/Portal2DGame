#ifndef COMPUERTA_H
#define COMPUERTA_H

#include "Box2D/Box2D.h"
#include "mundo.h"
#include "compuerta_logica.h"
#include "cuerpo.h"
#include "estado_compuerta.h"

// Compuerta del juego

class Compuerta : public Cuerpo{
    std::shared_ptr<CompuertaLogica> compuerta_logica;
	b2Body* cuerpo;
	b2Body* base;
	EstadoCompuerta* estado;
public:

	Compuerta(b2Vec2& pos, Mundo& mundo);
	Compuerta& operator=(Compuerta&& otra);
    // Recibe una compuerta logica de la cual se obtiene el estado booleando
    // para que se abra o no la compuerta.
    void agregarCompuertaLogica(std::shared_ptr<CompuertaLogica> compuerta);
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
