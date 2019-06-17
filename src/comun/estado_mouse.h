#ifndef ESTADO_MOUSE_H
#define ESTADO_MOUSE_H

#include "Box2D/Box2D.h"
#include <map>
#include "click.h"


class EstadoMouse{
	struct click izquierdo;
	struct click derecho;

public:
	EstadoMouse();
	// Constructor por movimiento.
	EstadoMouse(EstadoMouse &&otro);
	// Operador asignacion por movimiento.
	EstadoMouse& operator=(EstadoMouse &&otro);
	// Operador asignacion por copia.
	EstadoMouse& operator=(const EstadoMouse &otro);
	// Constructor por copia.
	EstadoMouse(const EstadoMouse &otro);
	// Se guarda la posicion del click y activa el click derecho
	// (booleano indicando que hubo un click derecho).
	void agregarClickDerecho(b2Vec2& pos_click);
	// Se guarda la posicion del click y activa el click izquierdo
	// (booleano indicando que hubo un click izquierdo).
	void agregarClickIzquierdo(b2Vec2& pos_click);
	// Devuelve un booleano indicando si hubo un click derecho.
	bool clickDerecho();
	// Devuelve un booleano indicando si hubo un click izquierdo.
	bool clickIzquierdo();
	// Devuelve la posicion del click derecho.
	b2Vec2& posClickDerecho();
	// Devuelve la posicion del click izquierdo.
	b2Vec2& posClickIzquierdo();
	// Resetea las 2 estructuras donde se guarda la informacion relativa a los
	// clicks.
	void resetear();
	~EstadoMouse() = default;
};

#endif //ESTADO_MOUSE_H
