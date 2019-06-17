#include "estado_mouse.h"

EstadoMouse::EstadoMouse(){
	derecho.clickeado = false;
	izquierdo.clickeado = false;
}

EstadoMouse::EstadoMouse(EstadoMouse &&otro) {
	if (this == &otro) {
		return;
	}
	derecho.clickeado = otro.derecho.clickeado;
	derecho.pos = otro.derecho.pos;
	izquierdo.clickeado = otro.izquierdo.clickeado;
	izquierdo.pos = otro.izquierdo.pos;
	otro.resetear();
}

EstadoMouse &EstadoMouse::operator=(EstadoMouse &&otro) {
	if (this == &otro) {
		return *this;
	}
	derecho.clickeado = otro.derecho.clickeado;
	derecho.pos = otro.derecho.pos;
	izquierdo.clickeado = otro.izquierdo.clickeado;
	izquierdo.pos = otro.izquierdo.pos;
	otro.resetear();
	return *this;
}

void EstadoMouse::agregarClickDerecho(b2Vec2& pos_click){
	derecho.clickeado = true;
	derecho.pos.Set(pos_click.x, pos_click.y);
}

void EstadoMouse::agregarClickIzquierdo(b2Vec2& pos_click){
	izquierdo.clickeado = true;
	izquierdo.pos.Set(pos_click.x, pos_click.y);
}

bool  EstadoMouse::clickDerecho(){
	return derecho.clickeado;
}

bool  EstadoMouse::clickIzquierdo(){
	return izquierdo.clickeado;
}

b2Vec2& EstadoMouse::posClickDerecho(){
	return derecho.pos;
}

b2Vec2& EstadoMouse::posClickIzquierdo(){
	return izquierdo.pos;
}

void EstadoMouse::resetear() {
	derecho.clickeado = false;
	derecho.pos.Set(0, 0);
	izquierdo.clickeado = false;
	izquierdo.pos.Set(0, 0);
}

EstadoMouse &EstadoMouse::operator=(const EstadoMouse &otro) {
    derecho.clickeado = otro.derecho.clickeado;
    derecho.pos = otro.derecho.pos;
    izquierdo.clickeado = otro.izquierdo.clickeado;
    izquierdo.pos = otro.izquierdo.pos;
    return *this;
}

EstadoMouse::EstadoMouse(const EstadoMouse &otro) {
    derecho.clickeado = otro.derecho.clickeado;
    derecho.pos = otro.derecho.pos;
    izquierdo.clickeado = otro.izquierdo.clickeado;
    izquierdo.pos = otro.izquierdo.pos;
}
