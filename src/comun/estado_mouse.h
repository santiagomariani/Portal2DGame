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
	EstadoMouse(EstadoMouse &&otro);
	EstadoMouse& operator=(EstadoMouse &&otro);
	EstadoMouse& operator=(const EstadoMouse &otro);
	EstadoMouse(const EstadoMouse &otro);
	void agregarClickDerecho(b2Vec2& pos_click);
	void agregarClickIzquierdo(b2Vec2& pos_click);
	bool clickDerecho();
	bool clickIzquierdo();
	b2Vec2& posClickDerecho();
	b2Vec2& posClickIzquierdo();
	void resetear();
	~EstadoMouse() = default;
};

#endif
