#include "pistola.h"
#include <iostream>
#include "ids.h"

Pistola::Pistola(Mundo& mundo) : mundo(mundo), d_azul(ID_DISPARO, mundo),
					 d_naranja(ID_DISPARO, mundo), p_azul(ID_PORTAL_AZUL, mundo),
					 p_naranja(ID_PORTAL_NARANJA, mundo){
	
    p_azul.conectar(&p_naranja);
	p_naranja.conectar(&p_azul);
	d_azul.setPortal(&p_azul);
	d_naranja.setPortal(&p_naranja);
}

void Pistola::dispararAzul(const b2Vec2& origen, const b2Vec2& destino){
	d_azul.activar(origen, destino);
}

void Pistola::dispararNaranja(const b2Vec2& origen, const b2Vec2& destino){
	d_azul.activar(origen, destino);
}
/*
Pistola& Pistola::operator=(Pistola&& otro){
    if (this == &otro){
        return *this;
    }
    mundo = std::move(otro.mundo);
    p_azul = std::move(otro.p_azul);
    p_naranja = std::move(otro.p_naranja);
    d_azul = std::move(otro.d_azul);
    d_naranja = std::move(otro.d_naranja);
    return *this;
}*/


Pistola::Pistola(Pistola&& otro):
            mundo(otro.mundo),   d_azul(std::move(otro.d_azul)),
            d_naranja(std::move(otro.d_naranja)), p_azul(std::move(otro.p_azul)),
            p_naranja(std::move(otro.p_naranja)){
    p_azul.conectar(&p_naranja);
    p_naranja.conectar(&p_azul);
    d_azul.setPortal(&p_azul);
    d_naranja.setPortal(&p_naranja);
}
