
#include "estado_mouse.h"

EstadoMouse::EstadoMouse(){
	derecho->clickeado = false;
	izquierdo->clickeado = false;
}


void EstadoMouse::agregarClickDerecho(b2Vec2& pos_click){
	derecho->clickeado = true;
	derecho->pos.Set(pos_click.x, pos_click.y);
}

void EstadoMouse::agregarClickIzquierdo(b2Vec2& pos_click){
	izquierdo->clickeado = true;
	izquierdo->pos.Set(pos_click.x, pos_click.y);
}

bool  EstadoMouse::clickDerecho(){
	return derecho->clickeado;
}

bool  EstadoMouse::clickIzquierdo(){
	return izquierdo->clickeado;
}

b2Vec2& EstadoMouse::posClickDerecho(){
	return derecho->pos;
}

b2Vec2& EstadoMouse::posClickIzquierdo(){
	return izquierdo->pos;
}

