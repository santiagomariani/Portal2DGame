#include "pistola.h"

Pistola::Pistola() : d_azul(5), d_naranja(6), p_azul(7), p_naranja(8){
	
	p_azul.conectar(&p_naranja);
	p_naranja.conectar(&p_azul);
	d_azul.setPortal(&p_azul);
	d_naranja.setPortal(&p_naranja);
}

void Pistola::dispararAzul(Mundo& mundo, const b2Vec2& origen, const b2Vec2& destino){
	d_azul.activar(mundo, origen, destino);
}

void Pistola::dispararNaranja(Mundo& mundo, const b2Vec2& origen, const b2Vec2& destino){
	d_azul.activar(mundo, origen, destino);
}
